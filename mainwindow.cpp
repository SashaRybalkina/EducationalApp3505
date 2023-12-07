#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#include <QVBoxLayout>
#include <map>

MainWindow::MainWindow(World &world, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), world(world)
{
    ui->setupUi(this);
    world.startWorld(this);
    camera = new Camera(world, this);
    qDebug() << "ran mw";

    //std::map<std::string, QLabel> interactionDrawings;  // () assumes it is func, add to .h
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

    connect(camera, &Camera::triggerHeadline, this, &MainWindow::makeHeadlineVisible);

    connect(ui->nounsButton, &QPushButton::clicked, this, &MainWindow::makeNounVisible);
    connect(ui->verbsButton, &QPushButton::clicked, this, &MainWindow::makeVerbVisible);
    connect(ui->adjectivesButton, &QPushButton::clicked, this, &MainWindow::makeAdjectiveVisible);

    connect(ui->headlineList, &QListWidget::itemPressed, this, &MainWindow::makeButtonsVisible);
    connect(ui->nounList, &QListWidget::itemPressed, this, &MainWindow::setString);
    connect(ui->verbList, &QListWidget::itemPressed, this, &MainWindow::setString);
    connect(ui->adjectiveList, &QListWidget::itemPressed, this, &MainWindow::setString);

    connect(this, &MainWindow::getTotalScore, &world, &World::updatePlayers);
    connect(&world, &World::displayInteraction, this, &MainWindow::displayInteraction);
    connect(&world, &World::removeInteraction, this, &MainWindow::removeInteraction);
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

void MainWindow::makeNounVisible()
{
    bool check = false;
    if (clickNounCounter % 2 == 0)
    {
        check = true;
    }
    ui->nounList->setVisible(check);
    clickNounCounter++;
}

void MainWindow::makeVerbVisible()
{
    bool check = false;
    if (clickVerbCounter % 2 == 0)
    {
        check = true;
    }
    ui->verbList->setVisible(check);
    clickVerbCounter++;
}

void MainWindow::makeAdjectiveVisible()
{
    bool check = false;
    if (clickAdjectiveCounter % 2 == 0)
    {
        check = true;
    }
    ui->adjectiveList->setVisible(check);
    clickAdjectiveCounter++;
}

void MainWindow::makeButtonsVisible(QListWidgetItem *currentSelection)
{
    currentSelection->setFlags(currentSelection->flags() & ~Qt::ItemIsEnabled);
    ui->headlineList->setEnabled(false);
    int headlineIndex = rand() % headlineBank.size();
    QString headline = headlineBank[headlineIndex];
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
        if (splitHeadline[i] == "<>" || splitHeadline[i] == "<>," || splitHeadline[i] == "<>.")
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
    emit getTotalScore(totalScore);
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
}

void MainWindow::displayInteraction(QPoint point, std::string interaction, std::string ID) {
    // Create new label
    QLabel* label = new QLabel(this);
    label->setText(QString::fromStdString(interaction));
    label->move(point);
    // Set the font to be bold and larger
    QFont font = label->font();
    font.setBold(true); // Make the font bold
    font.setPointSize(font.pointSize() + 4); // Increase the font size by 4 points
    label->setFont(font);
    label->show();
    // Store the label in the map
    interactionDrawings[ID] = label;
}

void MainWindow::removeInteraction(std::string ID)
{
    QLabel* label = interactionDrawings[ID];
    interactionDrawings.erase(ID);
    delete label;
}
