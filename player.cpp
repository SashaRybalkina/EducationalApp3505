#include "player.h"
#include <QPainter>
#include <QDebug>

Player::Player(std::string name, int x, int y,  int playerWidth, int playerHeight, QWidget *parent):
    QWidget(parent),
    name(name),
    x(x),
    y(y)
{
    qDebug() << playerWidth;
    setFixedSize(1000, 1000); // (playerWidth + 50, playerHeight + 50); // TODO move mobjects to back
}

void Player::setLocation(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Player::paintEvent(QPaintEvent *) {
    // qDebug() << "player painted: " << name;
    // Create a painter
    QPainter painter(this);;
    QImage image = QImage(":/person.png");
    painter.drawImage(x, y, image);
    // painter.drawImage(0, 0, image);
    // qDebug() << image;
    painter.end();
}
