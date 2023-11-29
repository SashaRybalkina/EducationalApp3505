#include "world.h"

World::World(QObject *parent, int game_width, int game_height):
    QObject(parent),
    game_width(game_width),
    game_height(game_height),
    timer(this)
{
    // player width/height based on size of sprite
    QImage image = QImage(":/people/stick_man.png");
    int player_width = image.width();
    int player_height = image.height();
    this->physicsEngine = new PhysicsEngine(10, player_width, player_height, game_width, game_height);

    for(const auto& [name, x, y] : physicsEngine->getPlayerLocations())
    {
        players[name] = new Player(name, x, y);
    }

    connect(&timer, &QTimer::timeout, this, &World::updateWorld);
    timer.start(10);  // 10 ms interval
}

void World::updateWorld()
{
    physicsEngine->updateWorld();
    for(const auto& [name, x, y] : physicsEngine->getPlayerLocations())
    {
        Player *player = players[name];
        player->setLocation(x, y);
        player->update();  // update triggers a paint event for that player which calls paintEvent
    }
}

