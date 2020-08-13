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

    // Connect all scene modifying widgets to rerender
    connect(ui->width, QOverload<int>::of(&QSpinBox::valueChanged), [=]{
        calculateRays();
        rerender();
    });
    connect(ui->height, QOverload<int>::of(&QSpinBox::valueChanged),[=]{
        calculateRays();
        rerender();
    });
    connect(ui->eye1, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::rerender);
    connect(ui->eye2, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::rerender);
    connect(ui->eye3, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::rerender);
    connect(ui->center1, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::rerender);
    connect(ui->center2, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::rerender);
    connect(ui->center3, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::rerender);
    connect(ui->up1, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::rerender);
    connect(ui->up2, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::rerender);
    connect(ui->up3, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::rerender);
    connect(ui->fov, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::rerender);
    connect(view, &View::cameraChanged, this, &MainWindow::rerender);


    connect(this, &MainWindow::updateImage, this, [=](QImage img){
        image->setPixmap(QPixmap::fromImage(img));
    }, Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    const unsigned int width = ui->width->value();
    const unsigned int height = ui->height->value();
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
    const unsigned int width = ui->width->value();
    const unsigned int height = ui->height->value();


    QImage img(width, height, QImage::Format_RGB888);

    //Create the scene (static so everything is const)
    const Sphere sphere(Vec3f(0, 1, 5), 2, Material(Vec3f(1.f, 0.0, 0.8), Vec3f(1.f, 0.0, 0.8), Vec3f(), 0.0));
    const Sphere sphere_2(Vec3f(5, 1, 5), 1, Material(Vec3f(0.0, 1.0, 0.8), Vec3f(0.0, 1.0, 0.8), Vec3f(), 0.0));
    const Light light(Vec3f(-1, 2, 0), Vec3f(1.f));
    const float ambient_intensity(0.5);

    const auto camera = view->getCamera();

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
            Intersection int_data_2(sphere_2.intersect(primary_ray));
            if(int_data.intersected || int_data_2.intersected) {
                num_hits++;
            }

            Color pixel_color;
            if(int_data.intersection_t < int_data_2.intersection_t) {
                pixel_color = Shader::shade_point(int_data, light, ambient_intensity);
            } else {
                pixel_color = Shader::shade_point(int_data_2, light, ambient_intensity);
            }

            //Write the pixel color into the final std::vector
            img.setPixel(x, y, pixel_color.to_qrgb());
            auto time = std::chrono::high_resolution_clock::now();
            if(std::chrono::duration_cast<std::chrono::milliseconds>(time - lasttime) > std::chrono::milliseconds(100)) {
                lasttime = time;
                emit updateImage(img);
            }
        }



    emit updateImage(img);
}
