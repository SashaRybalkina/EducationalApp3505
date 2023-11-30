#include "physicsengine.h"
#include <Box2D/Box2D.h>
#include <string>
#include <random>


PhysicsEngine::PhysicsEngine(int num_players, int playerWidth, int playerHeight, int game_width, int game_height):
    num_players(num_players),
    game_width(game_width),
    game_height(game_height),
    playerWidth(playerWidth),
    playerHeight(playerHeight)
{
    b2Vec2 gravity(0.0f, 0.0f); // Define world gravity
    this->world = new b2World(gravity);

    // create walls
    // gameWidth and gameHeight are the dimensions of simulation world in QT gui
    createWall(game_width / 2, 0, game_width, 1); // Top wall
    createWall(game_width / 2, - game_height, game_width, 1); // Bottom wall
    createWall(0, - game_height / 2, 1, game_height); // Left wall
    createWall(game_width, - game_height / 2, 1, game_height); // Right wall


    for (int i = 0; i < num_players; i++)
    {
        // create a body
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        int x = rand() % game_width;
        int y = rand() % game_height;
        std::tie(x, y) = pixelCoordinateToB2D(x, y);  // unpack
        bodyDef.position.Set(x, y);
        // get made body from world
        b2Body* body = world->CreateBody(&bodyDef);
        // Convert pixel dimensions to meters and create dynamic rectangle bound
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(playerWidth / 2.0f, playerHeight / 2.0f);  // divide by 2 because box2d doubles

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = .005f;
        fixtureDef.friction = 0.4f;
        fixtureDef.restitution = 0.6f; // Bounciness

        body->CreateFixture(&fixtureDef);
        std::string* name = new std::string(std::to_string(i));  // TODO: better way?
        body->SetUserData(name);
    }

}

void PhysicsEngine::createWall(float32 x, float32 y, float32 width, float32 height) {
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(x, y);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(width / 2, height / 2);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);
}

std::tuple<int, int> PhysicsEngine::pixelCoordinateToB2D(int x, int y)
{
    // QT has (0, 0) at top left, where as box2d has it at center
    // x = x - game_width / 2; // shift x = 0 to center rather than left side
    // y = -1 * (y - game_height / 2); // shfit y = 0 to center rather than top, then invert coordinates
    return std::make_tuple(x + (playerWidth / 2), - y - (playerHeight / 2));
}

std::tuple<int, int> PhysicsEngine::b2DCoordinateToPixel(int x, int y)
{
    // inverse of pixelCoordinateToB2D
    // x = x + game_width / 2;
    // y = (-1 * y) + (game_height / 2);
    return std::make_tuple(x - (playerWidth / 2), -1 * (y + (playerHeight / 2)));
}

float randomFloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

void PhysicsEngine::updateWorld()
{
    // It is generally best to keep the time step and iterations fixed.
    world->Step(1.0/60.0, 6, 2);

    // Iterate over all bodies and apply random forces
    for (b2Body* body = world->GetBodyList(); body; body = body->GetNext()) {
        if (body->GetType() == b2_dynamicBody) {
            float forceX = randomFloat(-10000.0f, 10000.0f);
            float forceY = randomFloat(-10000.0f, 10000.0f);
            b2Vec2 force(forceX, forceY);
            body->ApplyForceToCenter(force, true);
        }
    }
}


std::vector<std::tuple<std::string, int, int>> PhysicsEngine::getPlayerLocations()
{
    std::vector<std::tuple<std::string, int, int>> locations;
    for (b2Body* body = world->GetBodyList(); body; body = body->GetNext())
    {
        b2Vec2 position = body->GetPosition();

        // Retrieve the name
        std::string *name = static_cast<std::string*>(body->GetUserData());

        if (name)
        {  // check if has name cause walls also objects but without names
            // convert coordinates
            int x, y;
            std::tie(x, y) = b2DCoordinateToPixel(position.x, position.y);
            locations.push_back(std::make_tuple(*name, x, y));
        }
    }
    return locations;
}
