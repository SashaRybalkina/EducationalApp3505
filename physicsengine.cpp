#include "physicsengine.h"
#include <Box2D/Box2D.h>
#include <string>
#include <random>

float randomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

PhysicsEngine::PhysicsEngine(float32 numPlayers, float32 playerWidth, float32 playerHeight, float32 gameWidth, float32 gameHeight,
                             CallbackType collisionStartCallback, CallbackType collisionEndCallback) : numPlayers(numPlayers),
                                                                                                       gameWidth(gameWidth),
                                                                                                       gameHeight(gameHeight),
                                                                                                       playerWidth(playerWidth),
                                                                                                       playerHeight(playerHeight),
                                                                                                       collisionStartCallback(collisionStartCallback),
                                                                                                       collisionEndCallback(collisionEndCallback)
{
    b2Vec2 gravity(0.0f, 0.0f); // Define world without gravity
    this->world = new b2World(gravity);

    // Create walls
    // gameWidth and gameHeight are the dimensions of simulation world in QT gui
    createWall(gameWidth / 2, 0, gameWidth, 1);            // Top wall
    createWall(gameWidth / 2, -gameHeight, gameWidth, 1);  // Bottom wall
    createWall(0, -gameHeight / 2, 1, gameHeight);         // Left wall
    createWall(gameWidth, -gameHeight / 2, 1, gameHeight); // Right wall

    // Create players
    for (int i = 0; i < numPlayers; i++)
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        float32 x = randomFloat(0, gameWidth);
        float32 y = randomFloat(0, gameHeight);
        std::tie(x, y) = pixelCoordinateToB2D(x, y); // unpack
        bodyDef.position.Set(x, y);

        // Get made body from world
        b2Body *body = world->CreateBody(&bodyDef);

        // Convert pixel dimensions to meters and create dynamic rectangle bound
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(playerWidth / 2.0f - 20, playerHeight / 2.0f - 20); // divide by 2 because box2d doubles

        // set body traits
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = .005f;
        fixtureDef.friction = 1.0f;
        fixtureDef.restitution = 0.6f; // Bounciness

        // Apply traits and name (user data)
        body->CreateFixture(&fixtureDef);
        std::string *name = new std::string(std::to_string(i));
        body->SetUserData(name);

        // Create a larger sensor fixture for proximity detection for the body
        b2PolygonShape sensorShape;
        sensorShape.SetAsBox((playerWidth / 2.0f) + 10.0f, (playerHeight / 2.0f) + 10.0f); // 10 units larger on each side
        b2FixtureDef sensorFixtureDef;
        sensorFixtureDef.shape = &sensorShape;
        sensorFixtureDef.isSensor = true;
        body->CreateFixture(&sensorFixtureDef);
    }
    // Register contact listener with world
    this->cl = new ContactListener(this);
    world->SetContactListener(cl);
}

PhysicsEngine::ContactListener::ContactListener(PhysicsEngine *parent) : parent(parent)
{
}

void PhysicsEngine::ContactListener::BeginContact(b2Contact *contact)
{
    b2Fixture *fixtureA = contact->GetFixtureA();
    b2Fixture *fixtureB = contact->GetFixtureB();
    b2Body *bodyA = fixtureA->GetBody();
    b2Body *bodyB = fixtureB->GetBody();
    std::string *nameA = static_cast<std::string *>(bodyA->GetUserData());
    std::string *nameB = static_cast<std::string *>(bodyB->GetUserData());

    // Check if both fixtures are a sensor
    if (fixtureA->IsSensor() && fixtureB->IsSensor())
    {
        // Handle proximity enter event
        parent->collisionStartCallback(*nameA, *nameB);
    }
}

void PhysicsEngine::ContactListener::EndContact(b2Contact *contact)
{
    b2Fixture *fixtureA = contact->GetFixtureA();
    b2Fixture *fixtureB = contact->GetFixtureB();
    b2Body *bodyA = fixtureA->GetBody();
    b2Body *bodyB = fixtureB->GetBody();
    std::string *nameA = static_cast<std::string *>(bodyA->GetUserData());
    std::string *nameB = static_cast<std::string *>(bodyB->GetUserData());

    // Check if both fixtures are a sensor
    if (fixtureA->IsSensor() && fixtureB->IsSensor())
    {
        // Handle proximity leave event
        parent->collisionEndCallback(*nameA, *nameB);
    }
}

void PhysicsEngine::createWall(float32 x, float32 y, float32 width, float32 height)
{
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(x, y);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body *groundBody = world->CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(width / 2, height / 2);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);
}

std::tuple<float32, float32> PhysicsEngine::pixelCoordinateToB2D(float32 x, float32 y)
{
    // QT has (0, 0) at top left, where as box2d has it at center
    // x = x - gameWidth / 2; // shift x = 0 to center rather than left side
    // y = -1 * (y - gameHeight / 2); // shfit y = 0 to center rather than top, then invert coordinates
    return std::make_tuple(x + (playerWidth / 2), -y - (playerHeight / 2));
}

std::tuple<float32, float32> PhysicsEngine::b2DCoordinateToPixel(float32 x, float32 y)
{
    // Inverse of pixelCoordinateToB2D
    // x = x + gameWidth / 2;
    // y = (-1 * y) + (gameHeight / 2);
    return std::make_tuple(x - (playerWidth / 2), -1 * (y + (playerHeight / 2)));
}

void PhysicsEngine::updateWorld()
{
    // It is generally best to keep the time step and iterations fixed
    world->Step(1.0 / 60.0, 6, 2);

    // Iterate over all bodies and apply random forces
    for (b2Body *body = world->GetBodyList(); body; body = body->GetNext())
    {
        if (body->GetType() == b2_dynamicBody)
        {
            float forceX = randomFloat(-9000.0f, 9000.0f);
            float forceY = randomFloat(-9000.0f, 9000.0f);
            b2Vec2 force(forceX, forceY);
            body->ApplyForceToCenter(force, true);
        }
    }
}

std::vector<std::tuple<std::string, float32, float32>> PhysicsEngine::getPlayerLocations()
{
    std::vector<std::tuple<std::string, float32, float32>> locations;
    for (b2Body *body = world->GetBodyList(); body; body = body->GetNext())
    {
        b2Vec2 position = body->GetPosition();

        // Retrieve the name
        std::string *name = static_cast<std::string *>(body->GetUserData());

        if (name)
        { // Check if has name cause walls also objects but without names
            // Convert coordinates
            float32 x, y;
            std::tie(x, y) = b2DCoordinateToPixel(position.x, position.y);
            locations.push_back(std::make_tuple(*name, x, y));
        }
    }
    return locations;
}
