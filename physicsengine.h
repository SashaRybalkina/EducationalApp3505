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
    /**
     * @brief PhysicsEngine - responsible for running the physics of float32eraction
     * @param numPlayers - how many player sto create in simulation
     * @param playerWidth - width of player in pixel (use width of image)
     * @param playerHeight - height of player in pixel (use height of image)
     * @param gameWidth - screen width
     * @param gameHeight - screen height
     * @param collisionStartCallback - callback function to call each time two player enter eachothers sensor region
     * @param collisionEndCallback - callback function to call each time two player exit eachothers sensor region
     */
    PhysicsEngine(float32 numPlayers, float32 playerWidth, float32 playerHeight, float32 gameWidth, float32 gameHeight,
                  CallbackType collisionStartCallback,
                  CallbackType collisionEndCallback);

    /**
     * @brief createWall - builds wall that encloses physics simulation
     * @param x - position of wall (in pixels)
     * @param y - position of wall
     * @param width - of wall
     * @param height - of wall
     */
    void createWall(float32 x, float32 y, float32 width, float32 height);

    /**
     * @brief pixelCoordinateToB2D - converts from screen to physics engine coordinates
     * @param x - in pixels of screen
     * @param y - in pixels of screen
     * @return new coordinates
     */
    std::tuple<float32, float32> pixelCoordinateToB2D(float32 x, float32 y);

    /**
     * @brief b2DCoordinateToPixel - converts from physics coordinates to screen coordinates
     * @param x - in meters of Physics Engine quadrant IV
     * @param y - in meters of Physics Engine quadrant IV
     * @return new coordinates
     */
    std::tuple<float32, float32> b2DCoordinateToPixel(float32 x, float32 y);

    /**
     * @brief updateWorld - moves the physics engine one game step
     */
    void updateWorld();

    /**
     * @brief getPlayerLocations - gets current player locations in screen coordinates
     * @return a list of (id, x, y) pairs
     */
    std::vector<std::tuple<std::string, float32, float32>> getPlayerLocations();

    // void add_players(float32 num_players);
private:
    float32 numPlayers;
    float32 gameWidth;
    float32 gameHeight;
    float32 playerWidth;
    float32 playerHeight;
    b2World *world;
    CallbackType collisionStartCallback;
    CallbackType collisionEndCallback;

    class ContactListener : public b2ContactListener
    {
    public:
        /**
         * @brief ContactListener - used by physics engine to handle object sensor contact events
         * @param parent - the parent class the listener is encapsulated in so that it has access to callbacks
         */
        ContactListener(PhysicsEngine *parent);
        /**
         * @brief BeginContact - handles sensor detection
         * @param contact - collision start info
         */
        void BeginContact(b2Contact *contact) override;
        /**
         * @brief EndContact - handles sensor detection
         * @param contact - collision end info
         */
        void EndContact(b2Contact *contact) override;

    private:
        PhysicsEngine *parent;
    };

    ContactListener *cl;
};
#endif // PHYSICSENGINE_H
