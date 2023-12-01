#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "world.h"
#include "camera.h"
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(World &world, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    Ui::MainWindow *ui;
    World &world;
    Camera *camera;
    int clickMenuCounter = 0;
    int clickNounCounter = 0;
    int clickVerbCounter = 0;
    int clickAdjectiveCounter = 0;
    QString currentString = "";

    //<> are nouns, {} are verbs, [] are adjectives
    QList<QString> headlineBank = {"This morning, a [] VCJim supporter is seen with a [] Kopta supporter, ensuing a [] <>, which caused both individuals to {}."};

    QHash<QString, int> const verbBank = {{"hit", -15}, {"agree", 15}};

    QHash<QString, int> const adjectiveBank = {{"aggressive", -20}, {"friendly", 20}, {"hot", 10}, {"cool", 10}, {"dumb", -15}, {"smart", 15}, {"extravagant", -5}, {"modest", 5}, {"heroic", 20}, {"villainous", -25}};

    QString originalFrameStyle;
    QString changedFrameStyle;

public slots:
    void makeHeadlineVisible();
    void makeNounVisible();
    void makeVerbVisible();
    void makeAdjectiveVisible();
    void makeButtonsVisible(QListWidgetItem *currentSelection);
    void setString(QListWidgetItem *currentSelection);
    void editHeadline();
};
#endif // MAINWINDOW_H
