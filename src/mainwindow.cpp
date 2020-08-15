#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSpinBox>
#include <QPixmap>
#include <QtConcurrent/QtConcurrent>

#include "vec3f.h"
#include "ray.h"
#include "material.h"
#include "sphere.h"
#include "shader.h"
#include "light.h"
#include "camera.h"
#include "plane.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setup scene
    view = new View(this);
    ui->viewLayout->addWidget(view);
    scene = new QGraphicsScene();
    view->setScene(scene);
    image = new QGraphicsPixmapItem();
    scene->addItem(image);

    calculateRays();
    connectCameraControls();
    updateCameraControls(); // Reflect initial state as defined in the View


    connect(this, &MainWindow::updateImage, this, [=](QImage img){
        image->setPixmap(QPixmap::fromImage(img));
    }, Qt::QueuedConnection);
    connect(view, &View::cameraChanged, this, &MainWindow::rerender);
    connect(view, &View::cameraChanged, this, &MainWindow::updateCameraControls);

    // Trigger render
    rerender();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectCameraControls() {
    // Connect all scene modifying widgets to rerender
    connect(ui->width, QOverload<int>::of(&QSpinBox::valueChanged), [=](auto w){
        view->setWidth(w);
        calculateRays();
        rerender();
    });
    connect(ui->height, QOverload<int>::of(&QSpinBox::valueChanged), [=](auto h){
        view->setHeight(h);
        calculateRays();
        rerender();
    });

    auto eyeSetter = [=]{
        Vec3f eye(ui->eye1->value(), ui->eye2->value(), ui->eye3->value());
        view->setEye(eye);
    };
    connect(ui->eye1, QOverload<double>::of(&QDoubleSpinBox::valueChanged), eyeSetter);
    connect(ui->eye2, QOverload<double>::of(&QDoubleSpinBox::valueChanged), eyeSetter);
    connect(ui->eye3, QOverload<double>::of(&QDoubleSpinBox::valueChanged), eyeSetter);

    auto centerSetter = [=]{
        Vec3f center(ui->center1->value(), ui->center2->value(), ui->center3->value());
        view->setCenter(center);
    };
    connect(ui->center1, QOverload<double>::of(&QDoubleSpinBox::valueChanged), centerSetter);
    connect(ui->center2, QOverload<double>::of(&QDoubleSpinBox::valueChanged), centerSetter);
    connect(ui->center3, QOverload<double>::of(&QDoubleSpinBox::valueChanged), centerSetter);

    auto upSetter = [=]{
        Vec3f up(ui->up1->value(), ui->up2->value(), ui->up3->value());
        view->setUp(up);
    };
    connect(ui->up1, QOverload<double>::of(&QDoubleSpinBox::valueChanged), upSetter);
    connect(ui->up2, QOverload<double>::of(&QDoubleSpinBox::valueChanged), upSetter);
    connect(ui->up3, QOverload<double>::of(&QDoubleSpinBox::valueChanged), upSetter);

    connect(ui->fov, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::rerender);
}

void MainWindow::updateCameraControls() {
    auto camera = view->getCamera();

    ui->eye1->setValue(camera.eye.x);
    ui->eye2->setValue(camera.eye.y);
    ui->eye3->setValue(camera.eye.z);

    ui->center1->setValue(camera.center.x);
    ui->center2->setValue(camera.center.y);
    ui->center3->setValue(camera.center.z);

    ui->up1->setValue(camera.up.x);
    ui->up2->setValue(camera.up.y);
    ui->up3->setValue(camera.up.z);

    ui->width->setValue(camera.width);
    ui->height->setValue(camera.height);
}

void MainWindow::rerender() {
    static QFuture<void> future;

    if(future.isRunning()) {
        stop_flag = true;
        while(future.isRunning()){
            QThread::msleep(10); // bad!
        }
    }
    stop_flag = false;

    future = QtConcurrent::run(this, &MainWindow::render);
}

void MainWindow::calculateRays() {
    auto camera = view->getCamera();
    const unsigned int width = camera.width;
    const unsigned int height = camera.height;
    int tot_rays = width * height;

    rays.clear();
    rays.reserve(tot_rays);
    for(int x = 0; x < width; x++){
        for (int y = 0; y < height; y++) {
            rays.push_back({x,y});
        }
    }
    std::shuffle(rays.begin(), rays.end(), std::mt19937{std::random_device{}()});


}

void MainWindow::render() {
    const auto camera = view->getCamera();
    const unsigned int width = camera.width;
    const unsigned int height = camera.height;


    QImage img(width, height, QImage::Format_RGB888);

    //Create the scene (static so everything is const)
    const Sphere sphere(Vec3f(0, 1, 5), 2, Material(Vec3f(1.f, 0.0, 0.8), Vec3f(1.f, 0.0, 0.8), Vec3f(0.5f), 100.0));
    const Plane plane(Vec3f(0, -.95, 0), Vec3f(0, 1, 0),  Material(Vec3f(0.7, 0.5, 0.0), Vec3f(0.7, 0.5, 0.0), Vec3f(0.2f), 100.0));

    //Scene lights
    const Light light(Vec3f(-1, 2, 0), Vec3f(1.f));
    const float ambient_intensity(0.5);


    int num_hits(0);


    auto lasttime = std::chrono::high_resolution_clock::now();
    //Idea: parallelize the outer for loop
    for(const auto [x, y] : rays){
        if(stop_flag){
            break;
        }
        //Trace out a primary ray for a given pixel
        Ray primary_ray(camera.primary_ray(x, y));

        //Shoot out the ray and shade the potential intersection point
        Intersection int_data(sphere.intersect(primary_ray));
        Intersection int_data_2(plane.intersect(primary_ray));

        if(int_data.intersected || int_data_2.intersected) {
            num_hits++;
        }

        Color pixel_color;

        //Check to see which intersection came first
        if(int_data.intersection_t < int_data_2.intersection_t) {
            pixel_color = Shader::shade_point(int_data, light, ambient_intensity);
        } else {
            pixel_color = Shader::shade_point(int_data_2, light, ambient_intensity);
        }

        //Write the pixel color into the final std::vector
        img.setPixel(x, y, pixel_color.to_qrgb());

        // Update preview image at 30 fps
        /// @todo: This should obviously not be inside the compute loop, but updated asynchronously
        auto time = std::chrono::high_resolution_clock::now();
        if(std::chrono::duration_cast<std::chrono::milliseconds>(time - lasttime) > std::chrono::milliseconds(1000/30)) {
            lasttime = time;
            emit updateImage(img);
        }
    }

    emit updateImage(img);
}
