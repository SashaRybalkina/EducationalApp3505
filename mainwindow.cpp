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

    Camera *camera = new Camera(world, this);
//    QRect cameraRect = camera->getCameraRectangle();
//    camera->setGeometry(cameraRect.x(), cameraRect.y(), cameraRect.width(), cameraRect.height());

//    QRect cameraRect(0, 0, camera->width(), camera->height()); // Adjust with appropriate values
//    camera->setGeometry(cameraRect);

    //    setCentralWidget(camera);

    ui->mediaButton->raise();

    qDebug() << "ran mw";

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

    connect(ui->mediaButton, &QPushButton::clicked, this, &MainWindow::makeHeadlineVisible);
    connect(ui->nounsButton, &QPushButton::clicked, this, &MainWindow::makeNounVisible);
    connect(ui->verbsButton, &QPushButton::clicked, this, &MainWindow::makeVerbVisible);
    connect(ui->adjectivesButton, &QPushButton::clicked, this, &MainWindow::makeAdjectiveVisible);

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
    ui->nounsButton->setVisible(false);
    ui->verbsButton->setVisible(false);
    ui->adjectivesButton->setVisible(false);
    ui->headlineLabel->setVisible(check);
    ui->nounList->setVisible(false);
    ui->verbList->setVisible(false);
    ui->adjectiveList->setVisible(false);
    ui->headlineList->setVisible(check);
    ui->headlineList->setEnabled(true);
    ui->headlineTextBox->setVisible(false);
    ui->explanationLabel->setVisible(false);
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
            ui->headlineTextBox->setText(splitHeadline.join(" "));
            currentString = "";
            wordCount++;
        }
        else if (splitHeadline[i] == "{}" || splitHeadline[i] == "{}," || splitHeadline[i] == "{}.")
        {
            ui->nounsButton->setEnabled(false);
            ui->verbsButton->setEnabled(true);
            ui->adjectivesButton->setEnabled(false);
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
            ui->headlineTextBox->setText(splitHeadline.join(" "));
            currentString = "";
            wordCount++;
        }
        else if (splitHeadline[i] == "[]" || splitHeadline[i] == "[]," || splitHeadline[i] == "[].")
        {
            ui->nounsButton->setEnabled(false);
            ui->verbsButton->setEnabled(false);
            ui->adjectivesButton->setEnabled(true);
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
            ui->headlineTextBox->setText(splitHeadline.join(" "));
            currentString = "";
            wordCount++;
        }
    }
    totalScore = totalScore / wordCount;
    emit getTotalScore(totalScore);
}

