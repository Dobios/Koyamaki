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


    // Connect all scene modifying widgets to rerender
    connect(ui->width, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::rerender);
    connect(ui->height, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::rerender);
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


    connect(this, &MainWindow::updateImage, this, [=](QImage img){
        ui->image->setPixmap(QPixmap::fromImage(img));
    }, Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::rerender() {
    static QFuture<void> future;

    if(future.isRunning()) {
        future.cancel();
    }

    future = QtConcurrent::run(this, &MainWindow::render);
}

void MainWindow::render() {

    const unsigned int width = ui->width->value();
    const unsigned int height = ui->height->value();

    QImage img(width, height, QImage::Format_RGB888);

    //Create the scene (static so everything is const)
    const Sphere sphere(Vec3f(0, 1, 5), 2, Material(Vec3f(1.f, 0.0, 0.8), Vec3f(1.f, 0.0, 0.8), Vec3f(), 0.0));
    const Light light(Vec3f(-1, 2, 0), Vec3f(1.f));
    const float ambient_intensity(0.5);
    const Vec3f eye(ui->eye1->value(), ui->eye2->value(), ui->eye3->value());

    Camera camera(eye, Vec3f(ui->center1->value(), ui->center2->value(), ui->center3->value()), Vec3f(ui->up1->value(), ui->up2->value(), ui->up3->value()), ui->fov->value(), width, height);

    int num_hits(0);
    int tot_rays = width * height;

    auto lasttime = std::chrono::high_resolution_clock::now();

    //Idea: parallelize the outer for loop
    for(int x(0); x < width; ++x) {
        for(int y(0); y < height; ++y) {
            //Trace out a primary ray for a given pixel
            Ray primary_ray(camera.primary_ray(x, y));

            //Shoot out the ray and shade the potential intersection point
            Intersection int_data(sphere.intersect(primary_ray));
            if(int_data.intersected) {
                num_hits++;
            }

            Color pixel_color = Shader::shade_point(int_data, light, ambient_intensity);

            //Write the pixel color into the final std::vector
            img.setPixel(x, y, pixel_color.to_qrgb());
            auto time = std::chrono::high_resolution_clock::now();
            if(std::chrono::duration_cast<std::chrono::milliseconds>(time - lasttime) > std::chrono::milliseconds(100)) {
                lasttime = time;
                emit updateImage(img);
            }
        }
    }

    emit updateImage(img);
}
