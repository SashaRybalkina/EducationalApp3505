#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int clickMenuCounter = 0;
    int clickNounCounter = 0;
    int clickVerbCounter = 0;
    int clickAdjectiveCounter = 0;

public slots:
    void makeHeadlineVisible();
    void makeNounVisible();
    void makeVerbVisible();
    void makeAdjectiveVisible();
    void makeButtonsVisible();
};
#endif // MAINWINDOW_H
