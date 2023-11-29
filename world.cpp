#include "world.h"

World::World(int game_width, int game_height):
    game_width(game_width),
    game_height(game_height)
{
    // player width/height based on size of sprite
    this->physicsEngine = new PhysicsEngine(10, game_width / 10, game_height / 10, game_width, game_height);
}
