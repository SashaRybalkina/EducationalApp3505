#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <array>

class Player : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Player - holds player info
     * @param name - id of player
     * @param x - positioin on screen
     * @param y - positioin on screen
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
    void setScores(std::array<double, 3> scores);

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
    // 0 kopta_jim 1 apple_android 2 uofu_byu
    std::array<double, 3> scores;
};

#endif // PLAYER_H
