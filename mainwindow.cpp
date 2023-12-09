#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QVBoxLayout>
#include <map>

MainWindow::MainWindow(World &world, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), world(world)
{
    ui->setupUi(this);
    world.startWorld(this);
    camera = new Camera(world, this);

    ui->nounsButton->setVisible(false);
    ui->verbsButton->setVisible(false);
    ui->adjectivesButton->setVisible(false);
    ui->headlineLabel->setVisible(false);
    ui->nounList->setVisible(false);
    ui->verbList->setVisible(false);
    ui->adjectiveList->setVisible(false);
    ui->headlineList->setVisible(false);
    ui->headlineTextBox->setVisible(false);
    ui->explanationLabel->setVisible(false);
    ui->result->setVisible(false);

    connect(camera, &Camera::triggerHeadline, this, &MainWindow::makeHeadlineVisible);

    connect(ui->nounsButton, &QPushButton::clicked, ui->nounList, &QListWidget::setVisible);
    connect(ui->verbsButton, &QPushButton::clicked, ui->verbList, &QListWidget::setVisible);
    connect(ui->adjectivesButton, &QPushButton::clicked, ui->adjectiveList, &QListWidget::setVisible);

    connect(ui->headlineList, &QListWidget::itemPressed, this, &MainWindow::makeButtonsVisible);
    connect(ui->nounList, &QListWidget::itemPressed, this, &MainWindow::setString);
    connect(ui->verbList, &QListWidget::itemPressed, this, &MainWindow::setString);
    connect(ui->adjectiveList, &QListWidget::itemPressed, this, &MainWindow::setString);

    connect(this, &MainWindow::getTotalScore, &world, &World::updatePlayers);

    connect(&world, &World::displayInteraction, this, &MainWindow::displayInteraction);
    connect(&world, &World::removeInteraction, this, &MainWindow::removeInteraction);

    std::vector<QString> firstResult;
    std::vector<QString> secondResult;
    std::vector<QString> thirdResult;

    firstResult = {"You mostly made VCJim and Kopta supporters oppose each other. Your total score is ", "You mostly had little or no affect on VCJim and Kopta supporters. Your total score is ", "You mostly helped VCJim and Kopta supporters find a middle ground! Your total score is "};
    secondResult = {"You mostly made Android and Apple users oppose each other. Your total score is ", "You mostly had little or no affect on Android and Apple users. Your total score is ", "You mostly helped Android and Apple users find a middle ground! Your total score is "};
    thirdResult = {"You mostly made BYU and U of U students oppose each other. Your total score is ", "You mostly had little or no affect on BYU and U of U students. Your total score is ", "You mostly helped BYU and U of U students find a middle ground! Your total score is "};

    resultList.push_back(firstResult);
    resultList.push_back(secondResult);
    resultList.push_back(thirdResult);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeHeadlineVisible()
{
    ui->headlineLabel->setVisible(true);
    ui->headlineList->setVisible(true);
    ui->headlineList->setEnabled(true);
    ui->headlineTextBox->setVisible(true);
}

void MainWindow::makeButtonsVisible(QListWidgetItem *currentSelection)
{
    currentSelection->setFlags(currentSelection->flags() & ~Qt::ItemIsEnabled);
    ui->headlineList->setEnabled(false);
    int headlineIndex = rand() % headlineBank.size();
    QString headline = headlineBank[headlineIndex].mid(2, headlineBank[headlineIndex].length());
    indexTracker = headlineBank[headlineIndex].mid(0, 1).toInt();
    headlineBank.remove(headlineIndex);

    ui->headlineTextBox->setVisible(true);
    ui->explanationLabel->setVisible(true);
    ui->headlineTextBox->setText(headline);

    ui->nounsButton->setVisible(true);
    ui->verbsButton->setVisible(true);
    ui->adjectivesButton->setVisible(true);

    editHeadline();
}

void MainWindow::setString(QListWidgetItem *currentSelection)
{
    currentString = currentSelection->text();
}

void MainWindow::editHeadlineSimplifier(QString bracket, QListWidget *list, QStringList &splitHeadline, int &wordCount, int &totalScore, QHash<QString, int> const bank, int index)
{
    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    connect(list, &QListWidget::itemPressed, &loop, &QEventLoop::quit);
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start(100000);
    loop.exec();

    QString extra = "";
    if (bracket == '{')
    {
        if (splitHeadline[index].length() == 3)
        {
            extra = splitHeadline[index].mid(2, 2);
        }
        else if (currentString == "dance" || currentString == "agree" || currentString == "seperate" || currentString == "die")
        {
            currentString = currentString + " with";
        }
        else if (currentString == "eat. A LOT")
        {
            currentString = currentString + " of";
        }
    }
    else
    {
        if (splitHeadline[index].length() == 3)
        {
            extra = splitHeadline[index].mid(2, 2);
        }
    }

    splitHeadline[index] = currentString + extra;

    if (splitHeadline[index - 1] == "a" && (splitHeadline[index].mid(0, 1) == 'a' || splitHeadline[index].mid(0, 1) == 'o' || splitHeadline[index].mid(0, 1) == 'i' || splitHeadline[index].mid(0, 1) == 'e'))
    {
        splitHeadline[index - 1] = "an";
    }

    totalScore += bank.value(currentString);
    ui->headlineTextBox->setText(splitHeadline.join(" "));
    currentString = "";
    wordCount++;
}

void MainWindow::editHeadline()
{
    int totalScore = 0;
    int wordCount = 0;
    QStringList splitHeadline = (ui->headlineTextBox->toPlainText()).split(" ");
    for (int i = 0; i < splitHeadline.size(); i++)
    {
        if (splitHeadline[i] == "<>" || splitHeadline[i] == "<>," || splitHeadline[i] == "<>." || splitHeadline[i] == "<>!")
        {
            ui->nounsButton->setEnabled(true);
            ui->verbsButton->setEnabled(false);
            ui->adjectivesButton->setEnabled(false);
            ui->nounList->setVisible(true);
            ui->verbList->setVisible(false);
            ui->adjectiveList->setVisible(false);

            editHeadlineSimplifier("<", ui->nounList, splitHeadline, wordCount, totalScore, nounBank, i);
        }
        else if (splitHeadline[i] == "{}" || splitHeadline[i] == "{}," || splitHeadline[i] == "{}.")
        {
            ui->nounsButton->setEnabled(false);
            ui->verbsButton->setEnabled(true);
            ui->adjectivesButton->setEnabled(false);
            ui->nounList->setVisible(false);
            ui->verbList->setVisible(true);
            ui->adjectiveList->setVisible(false);

            editHeadlineSimplifier("{", ui->verbList, splitHeadline, wordCount, totalScore, verbBank, i);
        }
        else if (splitHeadline[i] == "[]" || splitHeadline[i] == "[]," || splitHeadline[i] == "[].")
        {
            ui->nounsButton->setEnabled(false);
            ui->verbsButton->setEnabled(false);
            ui->adjectivesButton->setEnabled(true);
            ui->nounList->setVisible(false);
            ui->verbList->setVisible(false);
            ui->adjectiveList->setVisible(true);

            editHeadlineSimplifier("[", ui->adjectiveList, splitHeadline, wordCount, totalScore, adjectiveBank, i);
        }
    }

    totalScore = totalScore / wordCount;
    // IndexTracker is the number associated with the headline. It indicates which x values need to be updated.
    emit getTotalScore(totalScore, indexTracker);

    // There are three different scores, a score for Kopta vs VCJim, a score for Apple vs Android, and a score for U of U vs BYU.
    // These scores are at at index 0, index 1, and index 2 in the list respectively.
    if (indexTracker == 1 || indexTracker == 2 || indexTracker == 7 || indexTracker == 8 || indexTracker == 10)
    {
        scoreList[0] += totalScore;
    }
    else if (indexTracker == 3 || indexTracker == 4 || indexTracker == 7 || indexTracker == 9 || indexTracker == 10)
    {
        scoreList[1] += totalScore;
    }
    else if (indexTracker == 5 || indexTracker == 6 || indexTracker == 8 || indexTracker == 9 || indexTracker == 10)
    {
        scoreList[2] += totalScore;
    }

    ui->nounsButton->setVisible(false);
    ui->verbsButton->setVisible(false);
    ui->adjectivesButton->setVisible(false);
    ui->headlineLabel->setVisible(false);
    ui->nounList->setVisible(false);
    ui->verbList->setVisible(false);
    ui->adjectiveList->setVisible(false);
    ui->headlineList->setVisible(false);
    ui->headlineList->setEnabled(false);
    ui->explanationLabel->setVisible(false);

    if (headlineBank.size() == 0)
    {
        // This sets up the result screen. There are three results that need to be specified based on their
        // respective scores and the scores themselves need to be displayed as well.
        QString str;
        for (int i = 0; i < scoreList.size(); i++)
        {
            if (-200 <= scoreList[i] <= -20)
            {
                statementList[i + 3] = resultList[i][0] + str.setNum(scoreList[i]);
            }
            else if (20 <= scoreList[i] <= 200)
            {
                statementList[i + 3] = resultList[i][2] + str.setNum(scoreList[i]);
            }
            else if (-20 < scoreList[i] < 20)
            {
                statementList[i + 3] = resultList[i][1] + str.setNum(scoreList[i]);
            }
        }

        ui->result->setVisible(true);

        QString statementText = statementList.join("\n\n");
        ui->result->setText(statementText);
    }
}

void setColor(QLabel *label, std::string interaction)
{
    // Pick color for label based on interaction type (interactions past into world in main)
    if (interaction == "shake hands")
    {
        label->setStyleSheet("QLabel { color : green; }");
    }
    else if (interaction == "discussion")
    {
        label->setStyleSheet("QLabel { color : darkgreen; }");
    }
    else if (interaction == "slander")
    {
        label->setStyleSheet("QLabel { color : red; }");
    }
    else if (interaction == "fight")
    {
        label->setStyleSheet("QLabel { color : darkred; }");
    }
}

void MainWindow::displayInteraction(QPoint point, std::string interaction, std::string player1, std::string player2)
{
    QLabel *label = new QLabel(this);
    label->setText(QString::fromStdString(interaction + " " + player1 + "&" + player2));
    label->move(point);

    QFont font = label->font();
    font.setBold(true);
    font.setPointSize(font.pointSize() + 4);
    setColor(label, interaction);
    label->setFont(font);
    label->adjustSize();
    label->show();

    // Store the label in the map
    std::string ID = player1 + player2;
    interactionDrawings[ID] = label;
}

void MainWindow::removeInteraction(std::string player1, std::string player2)
{
    std::string ID = player1 + player2;
    QLabel *label = interactionDrawings[ID];
    interactionDrawings.erase(ID);
    delete label;
}
