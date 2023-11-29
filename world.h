#ifndef WORLD_H
#define WORLD_H

#include "physicsengine.h"
#include <QObject>
#include <QTimer>


class World
{
public:
    World(int game_width, int game_height);
private:
    PhysicsEngine *physicsEngine;
    QTimer timer;
    int game_width;
    int game_height;
};

#endif // WORLD_H
