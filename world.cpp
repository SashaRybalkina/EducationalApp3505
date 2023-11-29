#include "world.h"

World::World(QObject *parent, int game_width, int game_height):
    QObject(parent),
    game_width(game_width),
    game_height(game_height),
    timer(this)
{
    // player width/height based on size of sprite
    this->physicsEngine = new PhysicsEngine(10, game_width / 10, game_height / 10, game_width, game_height);

    for(const auto& [name, x, y] : physicsEngine->getPlayerLocations())
    {
        players.push_back(Player(name, x, y))
    }

    connect(&timer, &QTimer::timeout, this, &SceneWidget::updateWorld);
    timer.start(10);  // 10 ms interval
}

void updateWorld()
{
    for(const Player &player : players) {

    }
}
