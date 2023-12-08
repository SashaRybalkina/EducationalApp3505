#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QScreen>
#include "world.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // get game width, height
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int width = screenGeometry.width();
    int height = screenGeometry.height();
    qDebug() << width;
    std::array<std::tuple<std::string, int>, 4> interactions = {std::make_tuple("discussion", -2), std::make_tuple("slander", 1), std::make_tuple("fight", -2), std::make_tuple("shake hands", 1)};
    World world(width, height, interactions);
    MainWindow w(world);
    w.show();
    return a.exec();
}
