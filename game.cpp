#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
}

Game::~Game()
{
    delete ui;
}

void Game::closeEvent (QCloseEvent *event){
    emit closed();
    event->accept();
}
