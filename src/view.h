#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

#include "camera.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(QWidget* parent = nullptr);

    Camera getCamera() const;

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent * event);

public slots:
    void setWidth(unsigned w);
    void setHeight(unsigned h);

signals:
    void cameraChanged();

private:
    Vec3f eye {0,1,0};
    Vec3f center{0,1,1};
    Vec3f up{0,1,0};
    float fov = 90.0;

    unsigned width = 480;
    unsigned height = 480;

    /**
     * @brief Camera movement handlers.
     * @todo: Perform proper math
     */
    void moveEye(const double dx, const double dy, const double dz);
    void moveCenter(const double dx, const double dy, const double dz);
    void moveUp(const double dx, const double dy, const double dz);



    /**
     * @brief lastClickPos
     * Store last click position to track changes in mouse movement.
     */
    QPointF lastClickPos;
};

#endif // VIEW_H
