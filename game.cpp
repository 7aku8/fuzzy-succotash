#include "game.h"
#include "ui_game.h"

#include "minmax.cpp"

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
    can_play = true;
    turns = 0;
    draw = false;
    winner = Ui::Field::None;

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

    // game initialization
    QObject::connect(ui->button_1, SIGNAL(pressed()), SLOT(set1()));
    QObject::connect(ui->button_2, SIGNAL(pressed()), SLOT(set2()));
    QObject::connect(ui->button_3, SIGNAL(pressed()), SLOT(set3()));
    QObject::connect(ui->button_4, SIGNAL(pressed()), SLOT(set4()));
    QObject::connect(ui->button_5, SIGNAL(pressed()), SLOT(set5()));
    QObject::connect(ui->button_6, SIGNAL(pressed()), SLOT(set6()));
    QObject::connect(ui->button_7, SIGNAL(pressed()), SLOT(set7()));
    QObject::connect(ui->button_8, SIGNAL(pressed()), SLOT(set8()));
    QObject::connect(ui->button_9, SIGNAL(pressed()), SLOT(set9()));

    srand( (unsigned)time(0) );

    init_game();
}

Game::~Game()
{
    delete ui;
}

void Game::closeEvent (QCloseEvent *event){
    emit closed();
    event->accept();
}

void Game::set1() { set_turn(1); }
void Game::set2() { set_turn(2); }
void Game::set3() { set_turn(3); }
void Game::set4() { set_turn(4); }
void Game::set5() { set_turn(5); }
void Game::set6() { set_turn(6); }
void Game::set7() { set_turn(7); }
void Game::set8() { set_turn(8); }
void Game::set9() { set_turn(9); }

void Game::set_player_character(Ui::Field character) {
    player_character = character;

    if (player_character == Ui::Field::X) {
        ui->your_character->setText("X");
    } else {
        ui->your_character->setText("O");
    }

    if (character != turn) {
        computer_turn();
    }
}

void Game::init_game() {
    // set random character to start game
    const float rand_number = rand();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = Ui::Field::None;
        }
    }

    if (rand_number < 0.5) {
        turn = Ui::Field::X;
    } else {
        turn = Ui::Field::O;
    }
    set_turn_indicator(turn);
}

void Game::fill_field(int field_number, Ui::Field field) {
    if (field == Ui::Field::X) {
        buttons[field_number - 1]->setText("X");
    } else if (field == Ui::Field::O) {
        buttons[field_number - 1]->setText("O");
    }

    buttons[field_number - 1]->setDisabled(true);
}

void Game::set_turn_indicator(Ui::Field turn) {
    if (turn == Ui::Field::X) {
        ui->whos_turn->setText("X");
    } else {
        ui->whos_turn->setText("O");
    }
}

void Game::set_turn(int field_number) {
    if (!can_play) { return; }
    if (turn != player_character) { return computer_turn(); }

    const int y = (field_number + 2) % 3;
    const int x = (field_number - 1) / 3;

    turns++;
    board[x][y] = turn;
    fill_field(field_number, turn);

    determine_winner(x, y, turn);
    switch_turn();
    set_turn_indicator(turn);

    computer_turn();
}

void Game::switch_turn() {
    if (turn == Ui::Field::O) {
        turn = Ui::Field::X;
    } else {
        turn = Ui::Field::O;
    }
}

void Game::computer_turn() {
    if (!can_play) { return; }

    Ui::Field opponent;
    if (player_character == Ui::Field::O) {
        opponent = Ui::Field::X;
    } else {
        opponent = Ui::Field::O;
    }

    Move bestMove = find_best_move(board, player_character, opponent);

    turns++;
    board[bestMove.y][bestMove.x] = turn;
    fill_field(3 * bestMove.y + bestMove.x + 1, turn);

    determine_winner(bestMove.x, bestMove.y, turn);
    switch_turn();
    set_turn_indicator(turn);
}

void Game::determine_winner(int x, int y, Ui::Field character) {
    if (board[y][0] == board[y][1] && board[y][1] == board[y][2] && board[y][0] == character) {
        return set_winner(character);
    }

    if (board[0][x] == board[1][x] && board[1][x] == board[2][x] && board[0][x] == character) {
        return set_winner(character);
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == character) {
        return set_winner(character);
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == character) {
        return set_winner(character);
    }

    // draw
    if (turns == (pow(3, 2) -1)) {
        return set_draw();
    }
}

void Game::set_draw() {
    std::cout << "DRAW" << std::endl;
    can_play = false;
}

void Game::set_winner(Ui::Field winner) {
    std::cout << "winner" << winner << std::endl;
    can_play = false;
}
