#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#include <QVBoxLayout>

MainWindow::MainWindow(World &world, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), world(world)
{
    ui->setupUi(this);
    world.startWorld(this);

    Camera *camera = new Camera(this);
    camera->setGeometry(10, 10, 500, 500);
//    setCentralWidget(camera);

    ui->media->raise();

    qDebug() << "ran mw";

    ui->nouns->setVisible(false);
    ui->verbs->setVisible(false);
    ui->adjectives->setVisible(false);
    ui->headlineLabel->setVisible(false);
    ui->nounList->setVisible(false);
    ui->verbList->setVisible(false);
    ui->adjectiveList->setVisible(false);
    ui->headlineList->setVisible(false);
    ui->headline->setVisible(false);
    ui->explanation->setVisible(false);

    connect(ui->media, &QPushButton::clicked, this, &MainWindow::makeHeadlineVisible);
    connect(ui->nouns, &QPushButton::clicked, this, &MainWindow::makeNounVisible);
    connect(ui->verbs, &QPushButton::clicked, this, &MainWindow::makeVerbVisible);
    connect(ui->adjectives, &QPushButton::clicked, this, &MainWindow::makeAdjectiveVisible);

    connect(ui->headlineList, &QListWidget::itemPressed, this, &MainWindow::makeButtonsVisible);
    connect(ui->nounList, &QListWidget::itemPressed, this, &MainWindow::setString);
    connect(ui->verbList, &QListWidget::itemPressed, this, &MainWindow::setString);
    connect(ui->adjectiveList, &QListWidget::itemPressed, this, &MainWindow::setString);

    connect(this, &MainWindow::getTotalScore, &world, &World::updatePlayers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeHeadlineVisible()
{
    bool check = false;
    if (clickMenuCounter % 2 == 0)
    {
        check = true;
    }
    ui->nouns->setVisible(false);
    ui->verbs->setVisible(false);
    ui->adjectives->setVisible(false);
    ui->headlineLabel->setVisible(check);
    ui->nounList->setVisible(false);
    ui->verbList->setVisible(false);
    ui->adjectiveList->setVisible(false);
    ui->headlineList->setVisible(check);
    ui->headlineList->setEnabled(true);
    ui->headline->setVisible(false);
    ui->explanation->setVisible(false);
    clickMenuCounter++;
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

    ui->headline->setVisible(true);
    ui->explanation->setVisible(true);
    ui->headline->setText(headline);

    ui->nouns->setVisible(true);
    ui->verbs->setVisible(true);
    ui->adjectives->setVisible(true);

    editHeadline();
}

void MainWindow::setString(QListWidgetItem *currentSelection)
{
    currentString = currentSelection->text();
}

void MainWindow::editHeadline()
{
    int totalScore = 0;
    int wordCount = 0;
    QStringList splitHeadline = (ui->headline->toPlainText()).split(" ");
    for (int i = 0; i < splitHeadline.size(); i++)
    {
        if (splitHeadline[i] == "<>" || splitHeadline[i] == "<>," || splitHeadline[i] == "<>.")
        {
            ui->nouns->setEnabled(true);
            ui->verbs->setEnabled(false);
            ui->adjectives->setEnabled(false);
            ui->nounList->setVisible(true);
            ui->verbList->setVisible(false);
            ui->adjectiveList->setVisible(false);

            QTimer timer;
            timer.setSingleShot(true);
            QEventLoop loop;
            connect(ui->nounList, &QListWidget::itemPressed, &loop, &QEventLoop::quit);
            connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
            timer.start(100000);
            loop.exec();

            QString extra = "";
            if (splitHeadline[i].length() == 3)
            {
                extra = splitHeadline[i].mid(2, 2);
            }

            splitHeadline[i] = currentString + extra;
            totalScore += nounBank.value(currentString);
            ui->headline->setText(splitHeadline.join(" "));
            currentString = "";
            wordCount++;
        }
        else if (splitHeadline[i] == "{}" || splitHeadline[i] == "{}," || splitHeadline[i] == "{}.")
        {
            ui->nouns->setEnabled(false);
            ui->verbs->setEnabled(true);
            ui->adjectives->setEnabled(false);
            ui->nounList->setVisible(false);
            ui->verbList->setVisible(true);
            ui->adjectiveList->setVisible(false);

            QTimer timer;
            timer.setSingleShot(true);
            QEventLoop loop;
            connect(ui->verbList, &QListWidget::itemPressed, &loop, &QEventLoop::quit);
            connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
            timer.start(100000);
            loop.exec();

            QString extra = "";
            if (splitHeadline[i].length() == 3)
            {
                extra = splitHeadline[i].mid(2, 2);
            }

            splitHeadline[i] = currentString + extra;
            totalScore += verbBank.value(currentString);
            ui->headline->setText(splitHeadline.join(" "));
            currentString = "";
            wordCount++;
        }
        else if (splitHeadline[i] == "[]" || splitHeadline[i] == "[]," || splitHeadline[i] == "[].")
        {
            ui->nouns->setEnabled(false);
            ui->verbs->setEnabled(false);
            ui->adjectives->setEnabled(true);
            ui->nounList->setVisible(false);
            ui->verbList->setVisible(false);
            ui->adjectiveList->setVisible(true);

            QTimer timer;
            timer.setSingleShot(true);
            QEventLoop loop;
            connect(ui->adjectiveList, &QListWidget::itemClicked, &loop, &QEventLoop::quit);
            connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
            timer.start(100000);
            loop.exec();

            QString extra = "";
            if (splitHeadline[i].length() == 3)
            {
                extra = splitHeadline[i].mid(2, 2);
            }

            splitHeadline[i] = currentString + extra;
            totalScore += adjectiveBank.value(currentString);
            ui->headline->setText(splitHeadline.join(" "));
            currentString = "";
            wordCount++;
        }
    }
    totalScore = totalScore/wordCount;
    emit getTotalScore(totalScore);
}
