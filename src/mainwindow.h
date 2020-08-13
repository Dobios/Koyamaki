#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
};

#endif // MAINWINDOW_H
