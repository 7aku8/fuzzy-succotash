#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QPushButton>

#include "selectcharacter.h"
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void select_character();
    void start_game_with_x();
    void start_game_with_o();
    void game_ended();
    void character_select_closed();

private:
    Ui::MainWindow *ui;

    Game *game;
    SelectCharacter *character;

    void start_game(Ui::Field character);
};
#endif // MAINWINDOW_H
