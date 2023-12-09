#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <array>

/**
 * @brief The Player class represents a person that can interact with other people in the world
 */
class Player : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Player - holds player info
     * @param name - id of player
     * @param x - position on screen
     * @param y - position on screen
     * @param playerWidth - width of player
     * @param playerHeight - height of player
     * @param gameWidth - width of world
     * @param gameHeight - height of world
     * @param parent - parent widget
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

    /**
     * @brief setScores - initialize scores
     * @param scores the scores representing player characteristics
     */
    void setScores(std::array<double, 3> scores);

    /**
     * @brief getX - getter for x
     * @return x
     */
    int getX() const { return x; }

    /**
     * @brief getY - getter for y
     * @return y
     */
    int getY() const { return y; }

    /**
     * @brief getName - getter for name
     * @return name
     */
    std::string getName() const { return name; }

    int playerWidth;
    int playerHeight;

private:
    std::string name;
    int x;
    int y;
    // 0 kopta_jim 1 apple_android 2 uofu_byu
    std::array<double, 3> scores;
};

#endif // PLAYER_H
