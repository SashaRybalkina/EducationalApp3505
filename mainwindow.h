#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "world.h"
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(World& world, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    World &world;
    int clickMenuCounter = 0;
    int clickNounCounter = 0;
    int clickVerbCounter = 0;
    int clickAdjectiveCounter = 0;
    QList<QString> headlineBank = {"one", "two", "three"};

public slots:
    void makeHeadlineVisible();
    void makeNounVisible();
    void makeVerbVisible();
    void makeAdjectiveVisible();
    void makeButtonsVisible(QListWidgetItem *currentSelection);
};
#endif // MAINWINDOW_H
