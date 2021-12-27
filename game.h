#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <iostream>
#include <QCloseEvent>

namespace Ui {
class Game;
}

class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

signals:
    void closed();

private:
    Ui::Game *ui;

    void closeEvent(QCloseEvent *event);
};

#endif // GAME_H
