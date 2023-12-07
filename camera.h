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
 * @brief The Camera class allows the user to take a picture of an interaction between players
 */
class Camera : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Camera - represents a rectangle that can take pictures of people and interactions
     * @param world -  world object containing information about environment
     * @param parent - parent widget
     */
    Camera(World &world, QWidget *parent = nullptr);

    /**
     * @brief getPlayersInPicture - gets players in the captured picture
     * @return map of players in the picture
     */
    std::map<std::string, Player *> getPlayersInPicture();

    /**
     * @brief getClosestInteracting - gets the closest interaction in the picture to the center of the picture
     * @return the two players in the closest interaction, if any
     */
    std::tuple<Player *, Player *> getClosestInteracting();

protected:
    /**
     * @brief paintEvent - overrides paint event to draw camera
     * @param event - paint event
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief mousePressEvent - overrides mouse press to handle camera logic
     * @param event - mouse press event
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief mouseReleaseEvent - overrides mouse release to handle camera logic
     * @param event - mouse release event
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

    /**
     * @brief mouseMoveEvent - overrides mouse move to handle camera movement
     * @param event - mouse move event
     */
    void mouseMoveEvent(QMouseEvent *event) override;

    /**
     * @brief wheelEvent - overrides wheel events to handle camera size
     * @param event - wheel event
     */
    void wheelEvent(QWheelEvent *event) override;

signals:
    /**
     * @brief triggerHeadline - emitted to show headline in mainwindow
     */
    void triggerHeadline();

private:
    World *world;
    QPoint pictureLocation;

    bool leftButtonPressed;
    bool rightButtonPressed;

    std::map<std::string, Player *> playersInPic;
};

#endif // CAMERA_H
