#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H
#include <Box2D/Box2D.h>
#include <tuple>

class PhysicsEngine
{
public:
    PhysicsEngine(int num_players, int player_width, int player_height, int game_width, int game_height);

    void createWall(float32 x, float32 y, float32 width, float32 height);

    std::tuple<int, int> pixelCoordinateToB2D(int x, int y);

    std::tuple<int, int> b2DCoordinateToPixel(int x, int y);

    void updateWorld();

    std::vector<std::tuple<std::string, int, int>> getPlayerLocations();



    // void add_players(int num_players);
private:
    int num_players;
    int game_width;
    int game_height;
    int playerWidth;
    int playerHeight;
    b2World *world;
};

#endif // PHYSICSENGINE_H
