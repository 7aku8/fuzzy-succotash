#ifndef SELECTCHARACTER_H
#define SELECTCHARACTER_H

#include <QDialog>
#include <QCloseEvent>

#include "field.h"

namespace Ui {
class SelectCharacter;
}

class SelectCharacter : public QDialog
{
    Q_OBJECT

public:
    explicit SelectCharacter(QWidget *parent = nullptr);
    ~SelectCharacter();

public slots:
    void choose_x();
    void choose_o();

signals:
    void set_x();
    void set_o();
    void closed();

private:
    Ui::SelectCharacter *ui;

    void closeEvent(QCloseEvent *event);
};

#endif // SELECTCHARACTER_H
