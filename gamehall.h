#ifndef GAMEHALL_H
#define GAMEHALL_H

#include <QWidget>
#include <QApplication>
namespace Ui {
class GameHall;
}

class GameHall : public QWidget
{
    Q_OBJECT

public:
    explicit GameHall(QWidget *parent = nullptr);
    ~GameHall();
    QString path=QApplication::applicationDirPath();

private:
    Ui::GameHall *ui;
};

#endif // GAMEHALL_H
