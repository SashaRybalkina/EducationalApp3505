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
    int clickNounCounter = 0;
    int clickVerbCounter = 0;
    int clickAdjectiveCounter = 0;
    QString currentString = "";
    int indexTracker = 0;

    //<> are nouns, {} are verbs, [] are adjectives
    QList<QString> headlineBank = {"1 At 5 pm, a <> is captured between a Kopta supporter and a VCJim supporter, with the Kopta supporter determined to {}, and VCJim supporter determined to {}.",
                                   "2 This morning, a [] VCJim supporter is seen with a [] Kopta supporter, ensuing a [] <>, which caused both individuals to {}.",
                                   "3 The blasphemy! A [] Apple user is planning a <> with a [] Android user, and many are expecting a <> to happen next.",
                                   "4 A <> last night has caused Apple users and Android users to {} one another, creating a [] sense of a <> in the local area.",
                                   "5 A message leak has exposed the [] intentions of a U of U student to {} a BYU student, and the BYU student will {} the U of U student in turn.",
                                   "6 Oh my! Did me just catch a <>, <>, or a <> between the U of U students and the BYU students? Either way, this will be a <> of the century.",
                                   "7 It looks like VCJim supporters have teamed up with Apple users to {} both Kopta supporters and Android users with a <>.",
                                   "8 A [] U of U student is seen at a nearby park with a [] Kopta supporter, seemingly planning a <> against all BYU students and VCJim supporters.",
                                   "9 Can you believe it? Now BYU students are teaming up with Apple users to {} U of U students and Android users.",
                                   "10 It's a full-blown <>! Now all parties are creating a [] <>, something never before seen in history."};

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
    void getTotalScore(int totalScore, int indexTracker);
};
#endif // MAINWINDOW_H
