#include "gamehall.h"
#include "ui_gamehall.h"
#include <QProcess>
GameHall::GameHall(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameHall)
{
    ui->setupUi(this);
    setWindowTitle("Game Hall!");
    connect(ui->pushButton,&QPushButton::clicked,[=]()
            {
        QProcess process(this);
        process.startDetached(path+"/games/five2line/five2line.exe");
    });
}

GameHall::~GameHall()
{
    delete ui;
}
