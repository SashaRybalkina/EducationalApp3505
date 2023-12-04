#include "world.h"
#include <QDebug>
#include <functional>

World::World(int game_width, int game_height, QObject *parent) : QObject(parent),
    timer(this),
    game_width(game_width),
    game_height(game_height)
{
}

void World::setParent(QWidget *parent)
{
    this->parent = parent;

    // player width/height based on size of sprite
    QImage image = QImage(":/person.png");
    int playerWidth = image.width();
    int playerHeight = image.height();
    // bind member method to instance of class
    auto boundStartCallback = std::bind(&World::collisionStartCallback, this, std::placeholders::_1, std::placeholders::_2);
    auto boundEndCallback = std::bind(&World::collisionEndCallback, this, std::placeholders::_1, std::placeholders::_2);
    // create physics engine
    this->physicsEngine = new PhysicsEngine(10, playerWidth, playerHeight, game_width, game_height, boundStartCallback, boundEndCallback);
    // create players with intial physics
    for (const auto &[name, x, y] : physicsEngine->getPlayerLocations())
    {
        // qDebug() << "ran world";
        Player *player = new Player(name, x, y, playerWidth, playerHeight, game_width, game_height, parent); // TODO: add image as parameter
        player->show();
        player->lower(); // moves to bottom of stack among widgets with same parent
        players[name] = player;
    }
    // set timer to update engine and in turn update world so gui can update
    connect(&timer, &QTimer::timeout, this, &World::updateWorld);
    timer.start(10); // 10 ms interval
}

void World::updateWorld()
{
    // qDebug() << "world called updateWorld";
    physicsEngine->updateWorld();
    for (const auto &[name, x, y] : physicsEngine->getPlayerLocations())
    {
        // qDebug() << "ran";
        Player *player = players[name];
        player->setLocation(x, y);
        player->update(); // update triggers a paint event for that player which calls paintEvent
    }
}

void World::updatePlayers(int totalScore)
{
    for (const auto &player : players)
    {
        mathEngine->updateAndGetNewY(player.first, totalScore);
    }
}

void World::collisionStartCallback(std::string player1, std::string player2)
{
//    qDebug() << player1 << player2 << "start";
    activeCollisions.insert(std::make_tuple(player1, player2));
}

void World::collisionEndCallback(std::string player1, std::string player2)
{
//    qDebug() << player1 << player2 << "end";
    activeCollisions.erase(std::make_tuple(player1, player2));
}

