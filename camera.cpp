#include "camera.h"

Camera::Camera(World &world, QWidget *parent)
    : world(&world), QWidget(parent), leftButtonPressed(false), rightButtonPressed(false), ctrlPressed(false)
{
//    rectangle = QRect(0, 0, 100, 100);
    // resize(100, 100);
    qDebug() << "camera created";

}

std::map<std::string, Player *> Camera::getPlayersInPicture()
{
//    playersInPicture.clear();

//    for (const auto &[name, player] : world->getPlayers())
//    {
//        QRect playerRect(player->getX(), player->getY(), player->width(), player->height());

//        if (rectangle.intersects(playerRect))
//        {
//            playersInPicture[name] = player;
//        }
//    }

//    qDebug() << "Players in picture: ";
//    for (const auto &[name, player] : playersInPicture)
//    {
//        qDebug() << name;
//    }

//    return playersInPicture;

    playersInPicture.clear();

    for (const auto &[name, player] : world->getPlayers())
    {
        QRect playerRect(player->getX(), player->getY(), player->width(), player->height());

        // Use the widget's dimensions directly instead of 'rectangle'
        if (QRect(0, 0, width(), height()).intersects(playerRect))
        {
            playersInPicture[name] = player;
        }
    }

    qDebug() << "Players in picture: ";
    for (const auto &[name, player] : playersInPicture)
    {
        qDebug() << name;
    }

    return playersInPicture;
}

std::tuple<Player *, Player *> Camera::getClosestInteracting()
{
//    const std::set<std::tuple<std::string, std::string>> &collisions = world->getActiveCollisions();
//    playersInPicture = getPlayersInPicture();

//    Player *closestInteractingPlayer1 = nullptr;
//    Player *closestInteractingPlayer2 = nullptr;
//    double minDistance = std::numeric_limits<double>::max();

//    for (const auto &[player1, player2] : collisions)
//    {
//        // Check if both players are in the map returned from getPlayersInPicture()
//        if (playersInPicture.find(player1) != playersInPicture.end() &&
//                playersInPicture.find(player2) != playersInPicture.end())
//        {
//            Player *interactingPlayer1 = playersInPicture[player1];
//            Player *interactingPlayer2 = playersInPicture[player2];

//            // Calculate distance of interaction from center of picture
//            pictureLocation = rectangle.center();
//            double distance = std::hypot(interactingPlayer1->getX() - pictureLocation.x(),
//                                         interactingPlayer1->getY() - pictureLocation.y()) +
//                    std::hypot(interactingPlayer2->getX() - pictureLocation.x(),
//                               interactingPlayer2->getY() - pictureLocation.y());

//            // Update closest interaction
//            if (distance < minDistance)
//            {
//                minDistance = distance;
//                closestInteractingPlayer1 = interactingPlayer1;
//                closestInteractingPlayer2 = interactingPlayer2;
//            }
//        }
//    }

//    if (closestInteractingPlayer1 && closestInteractingPlayer2)
//    {
//        return std::make_tuple(closestInteractingPlayer1, closestInteractingPlayer2);
//    }
//    return std::make_tuple(nullptr, nullptr);
    const std::set<std::tuple<std::string, std::string>> &collisions = world->getActiveCollisions();
     playersInPicture = getPlayersInPicture();

     Player *closestInteractingPlayer1 = nullptr;
     Player *closestInteractingPlayer2 = nullptr;
     double minDistance = std::numeric_limits<double>::max();

     // Use the widget's dimensions directly to calculate the center
     QPoint pictureLocation(width() / 2, height() / 2);

     for (const auto &[player1, player2] : collisions)
     {
         // Check if both players are in the map returned from getPlayersInPicture()
         if (playersInPicture.find(player1) != playersInPicture.end() &&
                 playersInPicture.find(player2) != playersInPicture.end())
         {
             Player *interactingPlayer1 = playersInPicture[player1];
             Player *interactingPlayer2 = playersInPicture[player2];

             // Calculate distance of interaction from center of picture
             double distance = std::hypot(interactingPlayer1->getX() - pictureLocation.x(),
                                          interactingPlayer1->getY() - pictureLocation.y()) +
                     std::hypot(interactingPlayer2->getX() - pictureLocation.x(),
                                interactingPlayer2->getY() - pictureLocation.y());

             // Update closest interaction
             if (distance < minDistance)
             {
                 minDistance = distance;
                 closestInteractingPlayer1 = interactingPlayer1;
                 closestInteractingPlayer2 = interactingPlayer2;
             }
         }
     }

     if (closestInteractingPlayer1 && closestInteractingPlayer2)
     {
         return std::make_tuple(closestInteractingPlayer1, closestInteractingPlayer2);
     }
     return std::make_tuple(nullptr, nullptr);
}

void Camera::paintEvent(QPaintEvent *event)
{
//    Q_UNUSED(event);

//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);

//    if (rightButtonPressed)
//    {
//        painter.setBrush(QBrush(QColor(0, 0, 0, 20)));
//        painter.setPen(QPen(QColor(255, 0, 0), 2));
//    }
//    else
//    {
//        painter.setBrush(QBrush(QColor(0, 0, 0, 10)));
//        painter.setPen(QPen(QColor(0, 0, 0), 2));
//    }

//    painter.drawRect(rectangle);
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

        // Use the widget's position directly
        painter.drawRect(QRect(0, 0, width(), height()));
}

void Camera::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        leftButtonPressed = true;

        dragStartPosition = event->pos();
                dragStartWidgetPosition = pos();
    }
    else if (event->button() == Qt::RightButton)
    {
        rightButtonPressed = true;
    }
    qDebug() << "mousePressEvent";
    update();
}

void Camera::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        leftButtonPressed = false;
        qDebug() << "mouse release left button";
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
        move(event->pos()/* - QPoint(width() / 2, height() / 2)*/);
        qDebug() << "Cursor pos: " << event->pos();
        qDebug() << "Widget pos: " << pos();
    }
    update();

//    if (leftButtonPressed)
//       {
//           // Calculate the offset between the current cursor position and the initial click position
//           QPoint offset = event->pos() - dragStartPosition;

//           // Calculate the new position based on the initial click position and the offset
//           QPoint newPosition = dragStartWidgetPosition + offset;

//           // Set the new position for the widget
//           move(newPosition);
//       }
//       update();
}

void Camera::wheelEvent(QWheelEvent *event)
{
    qDebug() << "wheel";
//    const int increment = 10;
//    const int step = (event->angleDelta().y() > 0) ? increment : -increment;

//    if (event->modifiers() & Qt::ControlModifier)
//    {
//        int newWidth = rectangle.width() + step;
//        if (newWidth > 10)
//        {
//            rectangle.setWidth(newWidth);
//        }
//    }
//    else
//    {
//        int newHeight = rectangle.height() + step;
//        if (newHeight > 10)
//        {
//            rectangle.setHeight(newHeight);
//        }
//    }
//    resize(rectangle.size());
//    update();
//    event->accept();

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
