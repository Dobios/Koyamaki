#include <QApplication>
#include <QFileInfo>
#include <QMessageBox>
#include <QResource>
#include <QTimer>
#include <iostream>

#include "src/mainwindow.h"

using namespace std;

int main(int argc, char** argv) {

    QApplication app(argc, argv);
    MainWindow m;

    m.show();
    return app.exec();
}
