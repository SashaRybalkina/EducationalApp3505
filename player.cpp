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
    QPainter painter(this);

    // Find correct sprite based on player characteristics
    QString imagePath = "images/"
            + QString(scores[0] > 0 ? "kopta" : (scores[0] < 0 ? "jim" : "zero"))
            + QString(scores[1] > 0 ? "Apple" : (scores[1] < 0 ? "Android" : "Zero"))
            + QString(scores[2] > 0 ? "Uu" : (scores[2] < 0 ? "Byu" : "Zero"))
            + ".png";
    QImage image(imagePath);

    painter.drawImage(x, y, image);
    playerWidth = image.width();
    playerHeight = image.height();

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
