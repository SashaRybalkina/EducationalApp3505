// camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QFrame>

class Camera : public QWidget
{
    Q_OBJECT

public:
    Camera(QFrame *frame, QWidget *parent = nullptr);
    void updatePosition(const QPoint &cursorPos);

protected:
private:
    QFrame *cameraFrame;
    bool leftButtonPressed;
};

#endif // CAMERA_H
