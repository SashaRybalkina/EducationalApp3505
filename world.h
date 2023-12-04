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
    World(int game_width, int game_height, QObject *parent = nullptr);

    void setParent(QWidget *parent);

    void collisionStartCallback(std::string player1, std::string player2);
    void collisionEndCallback(std::string player1, std::string player2);
    const std::map<std::string, Player*>& getPlayers() const{return players;}
    const std::set<std::tuple<std::string, std::string>>& getActiveCollisions() const {return activeCollisions;}

private:
    PhysicsEngine *physicsEngine;
    MathEngine *mathEngine;
    QTimer timer;
    int game_width;
    int game_height;
    QWidget *parent;

    std::map<std::string, Player *> players;
    std::set<std::tuple<std::string, std::string>> activeCollisions;

public slots:
    void updatePlayers(int totalScore);

private slots:
    void updateWorld();
};

#endif // WORLD_H
