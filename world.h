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
#include <array>

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
    World(int gameWidth, int gameHeight, std::array<std::tuple<std::string, int>, 4> interactions, QObject *parent = nullptr);
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
    const std::map<std::string, Player *> &getPlayers() const { return players; }
    const std::set<std::tuple<std::string, std::string>> &getActiveCollisions() const { return activeCollisions; }

public slots:
    /**
     * @brief updatePlayers uses the math engine to update specific stats of all players.
     * @param totalScore - the score to increment/decrement the stats by
     * @param index - helps specify the stats that need to be updated
     */
    void updatePlayers(int totalScore, int index);

signals:
    /**
     * @brief displayInteraction - tells mainWindow to display itneraciton type
     * @param point - to draw interaction
     * @param interaction - type of itneraciton happening
     * @param player1 - id
     * @param player2 - id
     */
    void displayInteraction(QPoint point, std::string interaction, std::string player1,  std::string player2);
    /**
     * @brief removeInteraction - tells mainWIndow to remove interaction
     * @param player1 - id
     * @param player2 - id
     */
    void removeInteraction(std::string player1,  std::string player2);

private:
    PhysicsEngine *physicsEngine;
    MathEngine *mathEngine;
    QTimer timer;
    int gameWidth;
    int gameHeight;
    int playerHeight;
    int playerWidth;
    QWidget *parent;

    std::map<std::string, Player *> players;
    std::set<std::tuple<std::string, std::string>> activeCollisions;
    const std::array<std::tuple<std::string, int>, 4> interactions;

private slots:
    /**
     * @brief updateWorld - moves the physics engine one step, gets back new locations, updates players, and redraws them
     */
    void updateWorld();
};

#endif // WORLD_H
