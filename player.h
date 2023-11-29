#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>

class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(std::string name, int x, int y, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

public slots:

signals:

private:
    std::string name;
    int x;
    int y;


};

#endif // PLAYER_H
