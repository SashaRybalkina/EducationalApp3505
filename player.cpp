#include "player.h"
#include <QPainter>

Player::Player(std::string name, int x, int y, int playerWidth, int playerHeight, int gameWidth, int gameHeight, QWidget *parent) : QWidget(parent),
                                                                                                                                    name(name),
                                                                                                                                    x(x),
                                                                                                                                    y(y)
{
    setFixedSize(gameWidth, gameHeight);
}

void Player::setLocation(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Player::setScores(std::array<double, 3> scores)
{
    this->scores = scores;
}

void Player::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // Find correct sprite based on player characteristics
    QString imagePath = ":images/" + QString(scores[0] > 0 ? "kopta" : (scores[0] < 0 ? "jim" : "zero")) + QString(scores[1] > 0 ? "Apple" : (scores[1] < 0 ? "Android" : "Zero")) + QString(scores[2] > 0 ? "Uu" : (scores[2] < 0 ? "Byu" : "Zero")) + ".png";
    QImage image = QImage(imagePath);

    painter.drawImage(x, y, image);
    playerWidth = image.width();
    playerHeight = image.height();

    // Set the painter to draw text in green
    QPen pen(Qt::black);
    painter.setPen(pen);

    // Set the font if you want to change the size or style
    QFont font = painter.font();
    painter.setFont(font);

    // Draw the text centered on the player image
    QRect textRect(x, y, playerWidth, playerHeight);
    painter.drawText(textRect, Qt::AlignTop | Qt::AlignLeft, QString::fromStdString(name));

    painter.end();
}
