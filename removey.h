#ifndef REMOVEY_H
#define REMOVEY_H

#include <QDialog>

namespace Ui {
class removeY;
}

class removeY : public QDialog
{
    Q_OBJECT

public:
    explicit removeY(QWidget *parent = nullptr);
    ~removeY();

private:
    Ui::removeY *ui;
};

#endif // REMOVEY_H
