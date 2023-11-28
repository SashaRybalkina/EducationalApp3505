#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->nouns->setVisible(false);
    ui->verbs->setVisible(false);
    ui->adjectives->setVisible(false);
    ui->headlineLabel->setVisible(false);
    ui->nounList->setVisible(false);
    ui->verbList->setVisible(false);
    ui->adjectiveList->setVisible(false);
    ui->headlineList->setVisible(false);

    connect(ui->media, &QPushButton::clicked, this, &MainWindow::makeHeadlineVisible);
    connect(ui->nouns, &QPushButton::clicked, this, &MainWindow::makeNounVisible);
    connect(ui->verbs, &QPushButton::clicked, this, &MainWindow::makeVerbVisible);
    connect(ui->adjectives, &QPushButton::clicked, this, &MainWindow::makeAdjectiveVisible);

    connect(ui->headlineList, &QListWidget::clicked, this, &MainWindow::makeButtonsVisible);
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

void MainWindow::makeButtonsVisible()
{
    ui->nouns->setVisible(true);
    ui->verbs->setVisible(true);
    ui->adjectives->setVisible(true);
}
