// camera.cpp
#include "camera.h"
#include <QMouseEvent>

Camera::Camera(QFrame *frame, QWidget *parent)
    : QWidget(parent), cameraFrame(frame), leftButtonPressed(false)
{
    setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

void Camera::updatePosition(const QPoint &cursorPos)
{
    cameraFrame->move(cursorPos.x() - cameraFrame->width() / 2, cursorPos.y() - cameraFrame->height() / 2);
}
