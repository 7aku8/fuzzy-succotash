#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QPushButton>
#include <cstdlib>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
    enum Field { None = ' ', X = 'X', O = 'O'};
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void game_start();
    void set1();
    void set2();
    void set3();
    void set4();
    void set5();
    void set6();
    void set7();
    void set8();
    void set9();

private:
    Ui::MainWindow *ui;
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
#endif // MAINWINDOW_H
