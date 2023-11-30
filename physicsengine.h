#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H
#include <Box2D/Box2D.h>
#include <tuple>
#include <functional>


class PhysicsEngine
{
public:
    // Define the type for the callbacks
    using CallbackType = std::function<void(std::string, std::string)>;
    PhysicsEngine(int num_players, int player_width, int player_height, int game_width, int game_height,
                  CallbackType collisionStartCallback,
                  CallbackType collisionEndCallback);  // had: void (*collisionEndCallback)(std::string, std::string)

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
    CallbackType collisionStartCallback;
    CallbackType collisionEndCallback;

    class ContactListener : public b2ContactListener
    {
    public:
        ContactListener(PhysicsEngine *parent);
        void BeginContact(b2Contact* contact) override;
        void EndContact(b2Contact* contact) override;
    private:
        PhysicsEngine *parent;
    };

    ContactListener *cl;


};

#endif // PHYSICSENGINE_H
