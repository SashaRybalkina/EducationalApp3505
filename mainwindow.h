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
    QList<QString> headlineBank = {"This morning, a [] VCJim supporter is seen with a [] Kopta supporter, ensuing a [] <>, which caused both individuals to {}.",
                                   "The blasphemy! A [] Kopta supporter is planning a <> with a [] VCJim supporter, and many are expecting a <> to happen next.",
                                   "A message leak has exposed the [] intentions of a VCJim supporter to {} a Kopta supporter, and the Kopta supporter will {} the VCJim supporter in turn.",
                                   "Oh my! Did me just catch a <>, <>, or a <> between the two opposing sides? Either way, this will be a <> of the century.",
                                   "A <> last night has caused the two opposing sides to {} one another, creating a [] sense of a <> in the local area."
                                    };

    QHash<QString, int> const nounBank = {{"fight", -15}, {"feast", 10}, {"war", -20}, {"love", 20}, {"celebration", 20}, {"argument", -10}, {"protest", -15}, {"battle of the GODS", 1000}, {"conversation", 10}, {"movie night", 15}};
    QHash<QString, int> const verbBank = {{"hit", -15}, {"agree", 15}, {"dance", 10}, {"die", -20}, {"seperate", 0}, {"hug", 20}, {"explode", -30}, {"kill", -20}, {"eat. A LOT", 0}, {"love", 20}};
    QHash<QString, int> const adjectiveBank = {{"aggressive", -20}, {"friendly", 20}, {"hot", 10}, {"cool", 10}, {"dumb", -15}, {"smart", 15}, {"extravagant", -5}, {"modest", 5}, {"heroic", 20}, {"villainous", -25}};

public slots:
    void makeHeadlineVisible();
    void makeNounVisible();
    void makeVerbVisible();
    void makeAdjectiveVisible();
    void makeButtonsVisible(QListWidgetItem *currentSelection);
    void setString(QListWidgetItem *currentSelection);
    void editHeadline();
    void editHeadlineSimplifier(QString bracket, QListWidget *list, QStringList &splitHeadline, int &wordCount, int &totalScore, QHash<QString, int> const bank, int index);

signals:
    void getTotalScore(int totalScore);
};
#endif // MAINWINDOW_H
