#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <iostream>
#include <QCloseEvent>
#include <QPushButton>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "field.h"

namespace Ui {
    class Game;
}

class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

    void set_player_character(Ui::Field character);

public slots:
    void set1();
    void set2();
    void set3();
    void set4();
    void set5();
    void set6();
    void set7();
    void set8();
    void set9();

signals:
    void closed();

private:
    Ui::Game *ui;

    void closeEvent(QCloseEvent *event);

    Ui::Field player_character;
    Ui::Field board[3][3];
    QPushButton * buttons[9];
    bool win;
    bool tie;
    int turns;

    bool draw;
    Ui::Field winner;

    bool can_play;

    Ui::Field turn;

    void set_turn(int field_number);
    void fill_field(int field_number, Ui::Field field);
    void set_turn_indicator(Ui::Field turn);
    void init_game();

    void switch_turn();
    void computer_turn();
    void determine_winner(int x, int y, Ui::Field character);
    void set_draw();
    void set_winner(Ui::Field winner);
};

#endif // GAME_H
