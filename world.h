#ifndef WORLD_H
#define WORLD_H

#include "physicsengine.h"
#include "player.h"
#include <QObject>
#include <QTimer>
#include <vector>


class World : public QObject
{
    Q_OBJECT
public:
    World(QObject *parent, int game_width, int game_height);

private:
    PhysicsEngine *physicsEngine;
    QTimer timer;
    int game_width;
    int game_height;
    std::vector<Player> players;

private slots:
    void updateWorld();

};

#endif // WORLD_H
