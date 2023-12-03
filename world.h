#ifndef WORLD_H
#define WORLD_H

#include "physicsengine.h"
#include "player.h"
#include "mathengine.h"
#include <QObject>
#include <QTimer>
#include <vector>
#include <map>
#include <set>

class World : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief World - holds the players the physics engine modeling their movment and the math engien calculating scores
     * @param gameWidth - screen width in pixels
     * @param gameHeight - screen height in pixels
     * @param parent - parent object
     */
    World(int gameWidth, int gameHeight, QObject *parent = nullptr);
    /**
     * @brief startWorld - creates player objects and adds their ids to the physics engine
     * @param parent - the main widget, need so player objects have the parent scope
     */
    void startWorld(QWidget *parent);

    /**
     * @brief collisionStartCallback - handles collision event from physis engine
     * @param player1 - in collision
     * @param player2 - in collision
     */
    void collisionStartCallback(std::string player1, std::string player2);
    /**
     * @brief collisionEndCallback - handles collision end event from physis engine
     * @param player1 - in collision
     * @param player2 - in collision
     */
    void collisionEndCallback(std::string player1, std::string player2);
    const std::map<std::string, Player*>& getPlayers() const{return players;}

public slots:
    void updatePlayers(int totalScore);

private:
    PhysicsEngine *physicsEngine;
    MathEngine *mathEngine;
    QTimer timer;
    int gameWidth;
    int gameHeight;
    std::map<std::string, Player *> players;
    QWidget *parent;
    std::set<std::tuple<std::string, std::string>> activeCollisions;



private slots:
    /**
     * @brief updateWorld - moves the physics engine one step, gets back new locations, updates players, and redraws them
     */
    void updateWorld();
};

#endif // WORLD_H
