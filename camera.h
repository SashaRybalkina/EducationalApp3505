#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include "world.h"

class Camera : public QWidget
{
    Q_OBJECT

public:
    Camera(QWidget *parent = nullptr);
    int numPlayersInPicture();


protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    World *world;
    QRect rectangle;
    QPoint center;
    QPoint pictureLocation;

    bool leftButtonPressed;
    bool rightButtonPressed;
    bool ctrlPressed;

    void updateRectSize(int step);
    void updateRectPos(const QPoint &pos);
};

#endif // CAMERA_H
