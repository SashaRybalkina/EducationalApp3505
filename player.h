#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>

class Player : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Player - holds player info
     * @param name
     * @param x
     * @param y
     * @param playerWidth
     * @param playerHeight
     * @param gameWidth
     * @param gameHeight
     * @param parent
     */
    explicit Player(std::string name, int x, int y, int playerWidth, int playerHeight, int gameWidth, int gameHeight, QWidget *parent = nullptr);
    /**
     * @brief paintEvent - redraws player in current location
     */
    void paintEvent(QPaintEvent *);
    /**
     * @brief setLocation - change location of player
     * @param x - on screen (top left)
     * @param y - on screen (top left)
     */
    void setLocation(int x, int y);

    int getX() const { return x; }
    int getY() const { return y; }

    std::string getName() const { return name; }
    int playerWidth;
    int playerHeight;

public slots:

signals:

private:
    std::string name;
    int x;
    int y;
};

#endif // PLAYER_H
