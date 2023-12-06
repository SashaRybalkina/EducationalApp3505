#include "camera.h"

Camera::Camera(World &world, QWidget *parent)
    : world(&world), QWidget(parent), leftButtonPressed(false), rightButtonPressed(false), ctrlPressed(false)
{
    resize(100, 100);
}

std::map<std::string, Player *> Camera::getPlayersInPicture()
{
    playersInPic.clear();

    // Check if camera intersects players
    for (const auto &[name, player] : world->getPlayers())
    {
        QRect playerRect(player->getX(), player->getY(), player->playerWidth, player->playerHeight);
        QRect cameraRect(this->pos().x(), this->pos().y(), width(), height());
        if (cameraRect.intersects(playerRect))
        {
            playersInPic[name] = player;
        }
    }

    qDebug() << "Players in picture: ";
    for (const auto &[name, player] : playersInPic)
    {
        qDebug() << name;
    }

    return playersInPic;
}

std::tuple<Player *, Player *> Camera::getClosestInteracting()
{
    const std::set<std::tuple<std::string, std::string>> &collisions = world->getActiveCollisions();

    Player *closestP1 = nullptr;
    Player *closestP2 = nullptr;
    double minDistance = std::numeric_limits<double>::max();

    // Middle of picture
    QPoint picLocation(this->pos().x() + width() / 2, this->pos().y() + height() / 2);

    playersInPic = getPlayersInPicture();
    for (const auto &[player1, player2] : collisions)
    {
        // If both players are in the picture
        if (playersInPic.find(player1) != playersInPic.end() && playersInPic.find(player2) != playersInPic.end())
        {
            Player *p1 = playersInPic[player1];
            Player *p2 = playersInPic[player2];

            // Calculate distance of interaction from center of picture
            double p1Dist = std::hypot((p1->getX() + p1->playerWidth / 2) - picLocation.x(),
                                       (p1->getY() + p1->playerHeight / 2) - picLocation.y());
            double p2Dist = std::hypot((p2->getX() + p2->playerWidth / 2) - picLocation.x(),
                                       (p2->getY()  + p2->playerHeight / 2) - picLocation.y());
            double distance = p1Dist + p2Dist;

            // Update closest interaction
            if (distance < minDistance)
            {
                minDistance = distance;
                closestP1 = p1;
                closestP2 = p2;
            }
        }
    }

    // If found a closest interaction, return the players
    if (closestP1 && closestP2)
    {
        emit triggerHeadline();
        return std::make_tuple(closestP1, closestP2);
    }
    return std::make_tuple(nullptr, nullptr);
}

void Camera::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (rightButtonPressed)
    {
        painter.setBrush(QBrush(QColor(0, 0, 0, 20)));
        painter.setPen(QPen(QColor(255, 0, 0), 2));
    }
    else
    {
        painter.setBrush(QBrush(QColor(0, 0, 0, 10)));
        painter.setPen(QPen(QColor(0, 0, 0), 2));
    }
    painter.drawRect(QRect(0, 0, width(), height()));
}

void Camera::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        leftButtonPressed = true;
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

        auto [player1, player2] = getClosestInteracting();
        if (player1 && player2)
        {
            qDebug() << "Players in closest interaction: " << player1->getName() << " and " << player2->getName();
        }
        else
        {
            qDebug() << "No players in picture are interacting";
        }

        update();
    }
}

void Camera::mouseMoveEvent(QMouseEvent *event)
{
    if (leftButtonPressed)
    {
        // widget position + cursor position
        move((this->pos() + event->pos()) - QPoint(width() / 2, height() / 2));
        //        qDebug() << "Cursor pos: " << event->pos();
        //        qDebug() << "Widget pos: " << pos();
    }
    update();
}

void Camera::wheelEvent(QWheelEvent *event)
{    
    const int increment = 10;
    const int step = (event->angleDelta().y() > 0) ? increment : -increment;

    if (event->modifiers() & Qt::ControlModifier)
    {
        int newWidth = width() + step;
        if (newWidth > 10)
        {
            setFixedWidth(newWidth);
        }
    }
    else
    {
        int newHeight = height() + step;
        if (newHeight > 10)
        {
            setFixedHeight(newHeight);
        }
    }
    update();
    event->accept();
}
