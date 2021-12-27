#include "selectcharacter.h"
#include "ui_selectcharacter.h"

SelectCharacter::SelectCharacter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectCharacter)
{
    ui->setupUi(this);

    connect(ui->button_o, SIGNAL(pressed()), this, SLOT(choose_o()));
    connect(ui->button_x, SIGNAL(pressed()), this, SLOT(choose_x()));
}

void SelectCharacter::closeEvent (QCloseEvent *event){
    emit closed();
    event->accept();
}

SelectCharacter::~SelectCharacter()
{
    delete ui;
}

void SelectCharacter::choose_o() {
    emit set_o();
}

void SelectCharacter::choose_x() {
    emit set_x();
}
