#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // initialize variables
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            board[i][j] = Ui::Field::None;
        }
    }
    game = nullptr;
    win = false;
    tie = false;
    can_play = false;
    no_win.reserve(9);

    for (size_t i = 0; i < 9; i++) {
        no_win.push_back(0);
    }

    buttons[0] = ui->button_1;
    buttons[1] = ui->button_2;
    buttons[2] = ui->button_3;
    buttons[3] = ui->button_4;
    buttons[4] = ui->button_5;
    buttons[5] = ui->button_6;
    buttons[6] = ui->button_7;
    buttons[7] = ui->button_8;
    buttons[8] = ui->button_9;

    turn = Ui::Field::None;
    turn_count = 0;

    // game initialization
    QObject::connect(ui->start_game, SIGNAL(clicked()), this, SLOT(game_start()));

    QObject::connect(ui->button_1, SIGNAL(pressed()), SLOT(set1()));
    QObject::connect(ui->button_2, SIGNAL(pressed()), SLOT(set2()));
    QObject::connect(ui->button_3, SIGNAL(pressed()), SLOT(set3()));
    QObject::connect(ui->button_4, SIGNAL(pressed()), SLOT(set4()));
    QObject::connect(ui->button_5, SIGNAL(pressed()), SLOT(set5()));
    QObject::connect(ui->button_6, SIGNAL(pressed()), SLOT(set6()));
    QObject::connect(ui->button_7, SIGNAL(pressed()), SLOT(set7()));
    QObject::connect(ui->button_8, SIGNAL(pressed()), SLOT(set8()));
    QObject::connect(ui->button_9, SIGNAL(pressed()), SLOT(set9()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::game_start() {
    // choosing player to start game
    float rand_number = rand();
    if (rand_number > 0.5) {
        turn = Ui::Field::X;
    } else {
        turn = Ui::Field::O;
    }

    can_play = true;
    std::cout << "starting the game" << std::endl;
}

void MainWindow::set1() { openNewWindow(); };
void MainWindow::set2() { set_turn(2); };
void MainWindow::set3() { set_turn(3); };
void MainWindow::set4() { set_turn(4); };
void MainWindow::set5() { set_turn(5); };
void MainWindow::set6() { set_turn(6); };
void MainWindow::set7() { set_turn(7); };
void MainWindow::set8() { set_turn(8); };
void MainWindow::set9() { set_turn(9); };

void MainWindow::fill_field(int field_number, Ui::Field field) {
    if (field == Ui::Field::X) {
        buttons[field_number - 1]->setText("X");
    } else if (field == Ui::Field::O) {
        buttons[field_number - 1]->setText("O");
    }
}

void MainWindow::set_turn(int field_number) {
    if (!can_play) { return; }

    std::cout << field_number << std::endl;
    const int y = (field_number + 2) % 3;
    const int x = (field_number - 1) / 3;

    board[x][y] = turn;
    fill_field(field_number, turn);

    if (turn == Ui::Field::O) {
        turn = Ui::Field::X;
    } else {
        turn = Ui::Field::O;
    }
}

void MainWindow::game_ended() {
    std::cout << "game ended!!!" << std::endl;

    delete game;
    game = nullptr;
}

void MainWindow::openNewWindow() {
    if (game == nullptr) {
        game = new Game();

        game->show();
        connect(game, SIGNAL(closed()), this, SLOT(game_ended()));
    }
}
