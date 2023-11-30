#include "world.h"
#include <QDebug>

World::World(int game_width, int game_height, QObject *parent):
    QObject(parent),
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
    this->physicsEngine = new PhysicsEngine(10, playerWidth, playerHeight, game_width, game_height);

    for(const auto& [name, x, y] : physicsEngine->getPlayerLocations())
    {
        // qDebug() << "ran world";
        Player *player = new Player(name, x, y, playerWidth, playerHeight, game_width, game_height, parent);  // TODO: add image as parameter
        player->show();
        player->lower();  // moves to bottom of stack among widgets with same parent
        players[name] = player;
    }

    connect(&timer, &QTimer::timeout, this, &World::updateWorld);
    timer.start(10);  // 10 ms interval
}


void World::updateWorld()
{
    // qDebug() << "world called updateWorld";
    physicsEngine->updateWorld();
    for(const auto& [name, x, y] : physicsEngine->getPlayerLocations())
    {
        // qDebug() << "ran";
        Player *player = players[name];
        player->setLocation(x, y);
        player->update();  // update triggers a paint event for that player which calls paintEvent
    }
}

