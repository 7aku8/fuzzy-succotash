#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    character = nullptr;
    game = nullptr;
    connect(ui->start_game_button, SIGNAL(pressed()), this, SLOT(select_character()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::select_character() {
    if (character == nullptr && game == nullptr) {
        character = new SelectCharacter();

        ui->start_game_button->setDisabled(true);

        character->show();
        connect(character, SIGNAL(set_x()), this, SLOT(start_game_with_x()));
        connect(character, SIGNAL(set_o()), this, SLOT(start_game_with_o()));
        connect(character, SIGNAL(closed()), this, SLOT(character_select_closed()));
    }
}

void MainWindow::start_game_with_o() {
    start_game(Ui::Field::O);
    character_select_closed();
}

void MainWindow::start_game_with_x() {
    start_game(Ui::Field::X);
    character_select_closed();
}

void MainWindow::start_game(Ui::Field character) {
    std::cout << character << std::endl;
    if (game == nullptr) {
        game = new Game();

        game->set_player_character(character);

        game->show();
        connect(game, SIGNAL(closed()), this, SLOT(game_ended()));
    }
}

void MainWindow::game_ended() {
    std::cout << "game ended!!!" << std::endl;

    ui->start_game_button->setDisabled(false);

    delete game;
    game = nullptr;
}

void MainWindow::character_select_closed() {
    ui->start_game_button->setDisabled(false);

    delete character;
    character = nullptr;
}
