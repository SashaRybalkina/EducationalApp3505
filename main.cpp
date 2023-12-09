#include "mainwindow.h"

#include <QApplication>
#include <QScreen>
#include "world.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Get game width, height
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int width = screenGeometry.width();
    int height = screenGeometry.height();

    // Create interactions and world
    std::array<std::tuple<std::string, int>, 4> interactions = {std::make_tuple("discussion", -2), std::make_tuple("slander", 1), std::make_tuple("fight", -2), std::make_tuple("shake hands", 1)};
    World world(width, height, interactions);
    MainWindow w(world);

    // Get background
    QPixmap background(":/background.jpg");

    // Resize image to fit the window dimensions
    background = background.scaled(screen->size(), Qt::IgnoreAspectRatio);

    // Set the background
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    w.setPalette(palette);
    w.show();

    return a.exec();
}
