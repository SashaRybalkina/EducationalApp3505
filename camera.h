#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <tuple>
#include <iostream>
#include <cmath>
#include "world.h"
#include "player.h"

class Camera : public QWidget
{
    Q_OBJECT

public:
    Camera(World &world, QWidget *parent = nullptr);
    std::map<std::string, Player *> getPlayersInPicture();
    std::tuple<Player *, Player *> getClosestInteracting();

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

    std::map<std::string, Player *> playersInPicture;
};

#endif // CAMERA_H
