#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <iostream>
#include <QCloseEvent>
#include <QPushButton>
#include <cstdlib>

namespace Ui {
    class Game;
    enum Field { None = ' ', X = 'X', O = 'O'};
}

class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

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

    Ui::Field board[3][3];
    QPushButton * buttons[9];
    bool win;
    bool tie;
    std::vector<int> no_win;

    bool can_play;

    Ui::Field turn;

    void set_turn(int field_number);
    void fill_field(int field_number, Ui::Field field);
    void set_turn_indicator(Ui::Field turn);
    void init_game();
};

#endif // GAME_H
