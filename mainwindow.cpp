#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(World& world, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , world(world)
{
    ui->setupUi(this);
    world.setParent(this);
    qDebug() << "ran mw";

}

MainWindow::~MainWindow()
{
    delete ui;
}

