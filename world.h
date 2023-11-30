#ifndef WORLD_H
#define WORLD_H

#include "physicsengine.h"
#include "player.h"
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

private:
    PhysicsEngine *physicsEngine;
    QTimer timer;
    int game_width;
    int game_height;
    std::map<std::string, Player*> players;
    QWidget *parent;
    std::set<std::tuple<std::string, std::string>> activeCollisions;

private slots:
    void updateWorld();

};

#endif // WORLD_H
