#include "view.h"

#include <QMouseEvent>
#include <QWheelEvent>


View::View(QWidget* parent) : QGraphicsView(parent)
{

}

Camera View::getCamera() const {
    return Camera(eye, center, up, fov, width, height);
}

void View::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton)
    {
        lastClickPos = event->pos();
        event->accept();
        return;
    }
}

void View::moveEye(const double dx, const double dy, const double dz) {
    ///@todo: math
    constexpr double eye_scale = 100;
    eye.x += dx / eye_scale;
    eye.y -= dy / eye_scale;
    eye.z += dz / eye_scale;
}

void View::moveCenter(const double dx, const double dy, const double dz) {
    ///@todo: math
    constexpr double center_scale = 100;
    center.x += dx / center_scale;
    center.y -= dy / center_scale;
    center.z += dz / center_scale;
}

void View::moveUp(const double dx, const double dy, const double dz) {
    ///@todo: math
    constexpr double up_scale = 100;
    up.x += dx / up_scale;
    up.y -= dy / up_scale;
    up.z += dz / up_scale;
}

void View::setWidth(unsigned w){
    width = w;
    emit cameraChanged();
}
void View::setHeight(unsigned h) {
    height = h;
    emit cameraChanged();
}

void View::mouseMoveEvent(QMouseEvent *event){
    auto buttons = event->buttons();
    if (buttons & Qt::LeftButton)
    {
        const QPointF dpos = event->pos() - lastClickPos;
        if(event->modifiers() & Qt::ShiftModifier) {
            moveEye(dpos.x(), dpos.y(), 0);
        } else if(event->modifiers() & Qt::ControlModifier) {
            moveUp(dpos.x(), dpos.y(), 0);
        } else {
            moveCenter(dpos.x(), dpos.y(), 0);
        }
        lastClickPos = event->pos();

        event->accept();
        emit cameraChanged();
        return;
    }
    event->ignore();
}

void View::wheelEvent(QWheelEvent* event) {
    const int amount = (event->delta() > 0 ? 1 : -1) * 20;

    if(event->modifiers() & Qt::ShiftModifier) {
        moveEye(0,0,amount);
    } else if(event->modifiers() & Qt::ControlModifier) {
        moveUp(0,0,amount);
    } else {
        moveCenter(0,0,amount);
    }
    event->accept();
    emit cameraChanged();
}
