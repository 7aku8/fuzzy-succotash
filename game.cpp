#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);

    // initialize variables
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            board[i][j] = Ui::Field::None;
        }
    }
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

Game::~Game()
{
    delete ui;
}

void Game::closeEvent (QCloseEvent *event){
    emit closed();
    event->accept();
}

void Game::fill_field(int field_number, Ui::Field field) {
    if (field == Ui::Field::X) {
        buttons[field_number - 1]->setText("X");
    } else if (field == Ui::Field::O) {
        buttons[field_number - 1]->setText("O");
    }
}

void Game::set_turn(int field_number) {
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
