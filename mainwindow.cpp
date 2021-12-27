#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    game = nullptr;
    connect(ui->start_game_button, SIGNAL(pressed()), this, SLOT(start_game()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start_game() {
    if (game == nullptr) {
        game = new Game();

        ui->start_game_button->setDisabled(true);

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
