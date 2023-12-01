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
    void setRightButtonPressed(bool pressed) { isRightButtonPressed = pressed; }
    void setPictureLocation(const QPoint &location) { pictureLocation = location;
                                                      qDebug() << "Camera Location: " << location;
                                                    }

protected:
private:
    QFrame *cameraFrame;
    bool leftButtonPressed;
    QPoint pictureLocation;
    bool isRightButtonPressed;

};

#endif // CAMERA_H
