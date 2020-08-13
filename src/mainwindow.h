#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "view.h"
#include "camera.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


signals:
    void updateImage(QImage);

private:
    Ui::MainWindow *ui;

    void render();
    void rerender();
    void calculateRays();

    bool stop_flag = false;

    View* view = nullptr;
    QGraphicsScene* scene = nullptr;
    QGraphicsPixmapItem* image =  nullptr;

    std::vector<std::pair<int, int>> rays;
};

#endif // MAINWINDOW_H
