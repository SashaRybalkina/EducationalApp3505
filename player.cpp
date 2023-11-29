#include "player.h"
#include <QPainter>

Player::Player(std::string name, int x, int y, QWidget *parent):
    QWidget(parent),
    name(name),
    x(x),
    y(y)
{

}

void Player::setLocation(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Player::paintEvent(QPaintEvent *) {
    // Create a painter
    QPainter painter(this);;
    QImage image = QImage(":/people/stick_man.png");
    painter.drawImage(x, y, image);
    painter.drawImage(200, 200, image);
    //    qDebug() << image;
    painter.end();
}
