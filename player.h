#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>

class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(std::string name, int x, int y, int playerWidth, int playerHeight, int gameWidth, int gameHeight, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void setLocation(int x, int y);

    int getX() const { return x; }
    int getY() const { return y; }

public slots:

signals:

private:
    std::string name;
    int x;
    int y;
};

#endif // PLAYER_H
