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
            board[i][j] = 'A';
            std::cout << board[i][j] << std::endl;
        }
    }
    win = false;
    tie = false;
    no_win.reserve(9);

    for (size_t i = 0; i < 9; i++) {
        no_win.push_back(0);
        std::cout << no_win[i] << std::endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

