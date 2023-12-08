#include "player.h"
#include <QPainter>
#include <QDebug>

Player::Player(std::string name, int x, int y, int playerWidth, int playerHeight, int gameWidth, int gameHeight, QWidget *parent) : QWidget(parent),
                                                                                                                                    name(name),
                                                                                                                                    x(x),
                                                                                                                                    y(y)
{
    // qDebug() << playerWidth;

    setFixedSize(gameWidth, gameHeight); // (playerWidth + 50, playerHeight + 50); // TODO move mobjects to back
}

void Player::setLocation(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Player::setScores(std::array<double, 3> scores)
{
    qDebug() << "ran set scores";
    this->scores = scores;
}

void Player::paintEvent(QPaintEvent *)
{
    // qDebug() << "player painted: " << name;
    QPainter painter(this);
    QImage image = QImage(":/person.png");
    painter.drawImage(x, y, image);
    playerWidth = image.width();
    playerHeight = image.height();
    // painter.drawImage(0, 0, image);
    // qDebug() << image;
    // Set the painter to draw text in green
    QPen pen(Qt::green);
    painter.setPen(pen);
    // Set the font if you want to change the size or style
    QFont font = painter.font();
    // font.setPointSize(); // Set the font size if needed
    // font.setBold(true); // Set the font to bold if needed
    painter.setFont(font);
    // Draw the text centered on the player image
    QRect textRect(x, y, playerWidth, playerHeight);
    painter.drawText(textRect, Qt::AlignCenter, QString::fromStdString(name));

    painter.end();
}
