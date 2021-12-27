#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <iostream>
#include <QCloseEvent>
#include <QPushButton>

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
    int turn_count;

    void set_turn(int field_number);
    void fill_field(int field_number, Ui::Field field);
};

#endif // GAME_H
