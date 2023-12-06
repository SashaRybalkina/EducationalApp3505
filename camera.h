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

/**
 * @brief The Camera class
 */
class Camera : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Camera -
     * @param world
     * @param parent
     */
    Camera(World &world, QWidget *parent = nullptr);
    /**
     * @brief getPlayersInPicture
     * @return
     */
    std::map<std::string, Player *> getPlayersInPicture();
    /**
     * @brief getClosestInteracting
     * @return
     */
    std::tuple<Player *, Player *> getClosestInteracting();

protected:
    /**
     * @brief paintEvent
     * @param event
     */
    void paintEvent(QPaintEvent *event) override;
    /**
     * @brief mousePressEvent
     * @param event
     */
    void mousePressEvent(QMouseEvent *event) override;
    /**
     * @brief mouseReleaseEvent
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event) override;
    /**
     * @brief mouseMoveEvent
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event) override;
    /**
     * @brief wheelEvent
     * @param event
     */
    void wheelEvent(QWheelEvent *event) override;

signals:
    /**
     * @brief triggerHeadline
     */
    void triggerHeadline();

private:
    World *world;
    QPoint pictureLocation;

    bool leftButtonPressed;
    bool rightButtonPressed;
    bool ctrlPressed;

    std::map<std::string, Player *> playersInPicture;
};

#endif // CAMERA_H
