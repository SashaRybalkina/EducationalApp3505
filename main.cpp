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
    World world(width, height);
    MainWindow w(world);
    w.show();
    return a.exec();
}
