#include "world.h"
#include <QDebug>
#include <functional>
#include <cmath>
#include <random>


World::World(int gameWidth, int gameHeight, std::array<std::tuple<std::string, int>, 4> interactions, QObject *parent) : QObject(parent),
    timer(this),
    gameWidth(gameWidth),
    gameHeight(gameHeight),
    interactions(interactions)
{
    auto mathFunc = [](double x)
    {
        return std::tanh(x) * 20.0;
    };

    mathEngine = new MathEngine(mathFunc);
}

void World::startWorld(QWidget *parent)
{
    this->parent = parent;

    // player width/height based on size of sprite
    QImage image = QImage(":/zeroZeroZero.png");
    this->playerWidth = image.width();
    this->playerHeight = image.height();

    // bind member method to instance of class
    auto boundStartCallback = std::bind(&World::collisionStartCallback, this, std::placeholders::_1, std::placeholders::_2);
    auto boundEndCallback = std::bind(&World::collisionEndCallback, this, std::placeholders::_1, std::placeholders::_2);

    // create physics engine
    this->physicsEngine = new PhysicsEngine(10, playerWidth, playerHeight, gameWidth, gameHeight, boundStartCallback, boundEndCallback);

    // create players with intial physics
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_real_distribution<> distr(-20.0, 20.0); // Define the range
    for (const auto &[name, x, y] : physicsEngine->getPlayerLocations())
    {
        // qDebug() << "ran world";
        Player *player = new Player(name, x, y, playerWidth, playerHeight, gameWidth, gameHeight, parent); // TODO: add image as parameter
        std::array<double, 3> values;
        values = {distr(gen), distr(gen), distr(gen)};  // 3 random nums (-20, 20)
        mathEngine->addPlayer(name, values);
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
        // player->update(); // update triggers a paint event for that player which calls paintEvent
    }

    // After all locations are updated, then trigger paint events for all players
    for (auto &[name, player] : players)
    {
        player->update(); // This will now trigger paintEvent for each player
    }
}

void World::updatePlayers(int totalScore, int index)
{
    for (const auto &player : players)
    {
        player.second->setScores(mathEngine->updateAndGetNewY(player.first, totalScore, index));
    }
}

void World::collisionStartCallback(std::string player1, std::string player2)
{
    //    qDebug() << player1 << player2 << "start";
    activeCollisions.insert(std::make_tuple(player1, player2));
    Player *p1 = players[player1];
    Player *p2 = players[player2];
    QPoint displayLoc = QPoint((p1->getX() + p2->getX() + playerWidth) / 2, (p1->getY() + p2->getY() + playerHeight) / 2);  // ph/2 for each player so * 2 gets ph
    // generate interaction type and itneraciton delta
    std::string interaction;
    int scoreDelta;
    std::tie(interaction, scoreDelta) = interactions[rand() % interactions.size()];
    // apply math of interaciton and emit interaction for display
    p1->setScores(mathEngine->updateAndGetNewY(p1->getName(), scoreDelta, 10));
    p2->setScores(mathEngine->updateAndGetNewY(p2->getName(), scoreDelta, 10));
    qDebug() << "collision scores set";
    emit displayInteraction(displayLoc, interaction, player1, player2);

}

void World::collisionEndCallback(std::string player1, std::string player2)
{
    //    qDebug() << player1 << player2 << "end";
    activeCollisions.erase(std::make_tuple(player1, player2));
    emit removeInteraction(player1, player2);
}

