#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "world.h"
#include "camera.h"
#include <QListWidgetItem>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The MainWindow class holds all interactions and orchestrates logic
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow - constructor for main window
     * @param world -  world object containing information about environment
     * @param parent - parent widget
     */
    MainWindow(World &world, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    World &world;
    Camera *camera;
    QString currentString = "";
    int indexTracker = 0;
    int totalScore = 0;
    int wordCount = 0;

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
    QList<QString> copyForRestart = headlineBank;

    // Used for giving words point values
    QHash<QString, int> const nounBank = {{"fight", -15}, {"feast", 10}, {"war", -20}, {"love", 20}, {"celebration", 20}, {"argument", -10}, {"protest", -15}, {"battle of the GODS", 1000}, {"conversation", 10}, {"movie night", 15}};
    QHash<QString, int> const verbBank = {{"hit", -15}, {"agree", 15}, {"dance", 10}, {"die", -20}, {"seperate", 0}, {"hug", 20}, {"explode", -30}, {"kill", -20}, {"eat. A LOT", 0}, {"love", 20}};
    QHash<QString, int> const adjectiveBank = {{"aggressive", -20}, {"friendly", 20}, {"hot", 10}, {"cool", 10}, {"dumb", -15}, {"smart", 15}, {"extravagant", -5}, {"modest", 5}, {"heroic", 20}, {"villainous", -25}};
    std::map<std::string, QLabel *> interactionDrawings;
    std::vector<std::vector<QString>> resultList;
    std::array<int, 3> scoreList;
    QStringList statementList = {"Results!",
                                 "Throughout the game, you got to shape the world and the way that the characters felt about "
                                 "eachother through the use of media. You have made several wording choices that either made "
                                 "specific sides act more antagonistic towards eachother, or find a middle ground. At the end "
                                 "of the day, it did not matter what the real interaction was between the people whose picture "
                                 "you took for the headline, since the way that the interaction was painted held all of the "
                                 "power in manipulating the environment. This is how real-life media works as well, with many "
                                 "news articles often using partial lies and specific wording to get a specific agenda across.",
                                 "Here is how you influenced the environment:", "N/A. You ended the game too early, doofus.", "", ""};

public slots:
    /**
     * @brief makeHeadlineVisible allows the player to select a random headline
     */
    void makeHeadlineVisible();

    /**
     * @brief makeButtonsVisible displays nouns, verbs, and adjectives. saves a randomly selected headline
     * and its index to private instance variables.
     * @param currentSelection: selected item to be disabled
     */
    void makeButtonsVisible();

    /**
     * @brief setString keeps track of the currently selected word to place into the headline later.
     * @param currentSelection: the selected word
     */
    void setString(QListWidgetItem *currentSelection);

    /**
     * @brief editHeadline sets specific buttons and lists to be either visible or not visible and uses a
     * helper method to allow the user to insert specific words into specific spots in the headline. Once
     * the headline is completed, a total score is calculated based on the words used and the score is
     * sent out to edit the stats of the players.
     */
    void editHeadline();

    /**
     * @brief editHeadlineSimplifier uses logic to improve sentence coherency when a word is inserted.
     * For example, if the word inserted starts with a vowel and the previous word is "a", this logic will
     * change the "a" to be "an".
     * @param bracket - used to identify if the word is a verb.
     * @param list - the QListWidget that needs to be connected to the event loop.
     * @param splitHeadline - the list of all the words in the headline.
     * @param wordCount - keeps track of words inserted to help with total score calculation.
     * @param totalScore - sum of all points gathered from the words inserted.
     * @param bank - specific bank used for the type of word to get the word's point value.
     * @param index - used for replacing the bracket with a word.
     */
    void editHeadlineSimplifier(QString bracket, QListWidget *list, QStringList &splitHeadline, int &wordCount, int &totalScore, QHash<QString, int> const bank, int index);

    /**
     * @brief displayInteraction - displays the 'interactiton' label at the point of collision and stores the label in interactionDrawings
     * @param point - where the collision occured (center point between the two players)
     * @param interaction - label for interaction being had
     * @param ID -unique id of the collision
     */
    void displayInteraction(QPoint point, std::string interaction, std::string player1, std::string player2);

    /**
     * @brief removeInteraction - remove itneraciton from screen
     * @param player1 - id
     * @param player2 - id
     */
    void removeInteraction(std::string player1, std::string player2);
    /**
     * @brief endGame ends the game by making the result screen visible.
     */
    void endGame();
    /**
     * @brief restartGame resets all saved score and player values
     */
    void restartGame();
    /**
     * @brief calculateHeadline specifies the results of the game
     */
    void calculateHeadline();

signals:
    /**
     * @brief getTotalScore sends out a score that will affect a stat specified by index
     * @param totalScore - The score that will affect all the players' stats
     * @param indexTracker - Index of the headline that specifies the specific stats being altered
     */
    void getTotalScore(int totalScore, int indexTracker);
};
#endif // MAINWINDOW_H
