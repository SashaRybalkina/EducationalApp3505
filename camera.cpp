#include "camera.h"
#include <QPainter>
#include "player.h"

Camera::Camera(QWidget *parent)
    : QWidget(parent), leftButtonPressed(false), rightButtonPressed(false), ctrlPressed(false)
{
    rectangle = QRect(0, 0, 100, 100);
    center = rectangle.center();
}

int Camera::numPlayersInPicture()
{
    int count = 0;

//    world->testMethod();

//    qDebug() << world->getPlayers();

    //    for (const auto &[name, player] : world->getPlayers())
    //    {
    //        QRect playerRect(player->pos(), player->size());
    //        if (playerRect.intersects(rectangle))
    //        {
    //            count++;
    //        }
    //    }

    return count;
}

void Camera::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (rightButtonPressed) {
        painter.setBrush(QBrush(QColor(0, 0, 0, 20)));
        painter.setPen(QPen(QColor(255, 0, 0), 2));
    } else {
        painter.setBrush(QBrush(QColor(0, 0, 0, 10)));
        painter.setPen(QPen(QColor(0, 0, 0), 2));
    }

    painter.drawRect(rectangle);
}

void Camera::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        leftButtonPressed = true;
        updateRectPos(event->pos());
    }
    else if (event->button() == Qt::RightButton)
    {
        rightButtonPressed = true;
    }
    update();
}

void Camera::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        leftButtonPressed = false;
    }
    else if (event->button() == Qt::RightButton)
    {
        rightButtonPressed = false;
        pictureLocation = rectangle.center();

        int numPlayers = numPlayersInPicture();
        qDebug() << "Number of players in picture: " << numPlayers;

        update();
    }
}

void Camera::mouseMoveEvent(QMouseEvent *event)
{
    if (leftButtonPressed)
    {
        updateRectPos(event->pos());
    }
    update();
}

void Camera::wheelEvent(QWheelEvent *event)
{
    const int increment = 10;
    const int step = (event->angleDelta().y() > 0) ? increment : -increment;

    if (event->modifiers() & Qt::ControlModifier)
    {
        int newWidth = rectangle.width() + step;
        if (newWidth > 10)
        {
            rectangle.setWidth(newWidth);
            rectangle.moveCenter(center);
        }
    }
    else
    {
        updateRectSize(step);
    }
    update();
    event->accept();
}

void Camera::updateRectSize(int step)
{
    int newHeight = rectangle.height() + step;
    if (newHeight > 10)
    {
        rectangle.setHeight(newHeight);
        rectangle.moveCenter(center);
    }
}

void Camera::updateRectPos(const QPoint &pos)
{
    rectangle.moveCenter(pos);
    center = rectangle.center();
}
