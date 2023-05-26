 #include "signsucess.h"
#include "ui_signsucess.h"
#include <QPixmap>
#include <QPushButton>
#include "mainwindow.h"
#include "loginwindow.h"
SignSucess::SignSucess(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::SignSucess)
{
    ui->setupUi(this);

    setWindowTitle("注册成功啦！");
    setWindowIcon(QIcon(":/res/R-C3.jpg"));
    init();
    connect(ui->pushButton,&QPushButton::clicked,[=]()
    {
        emit Close();
        close();
        MainWindow *m = new MainWindow();
        m->show();
    });

}

SignSucess::~SignSucess()
{
    delete ui;
}

void SignSucess::init()
{
    QPixmap WA;
    WA.load(":/res/WA.jpg");
    QPixmap WA2= WA.scaled(221,331, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->WA->setPixmap(WA2);

    QPixmap sucess;
    sucess.load("://res/sucess.png");
    QPixmap sucess2= sucess.scaled(221,61, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->sucess->setPixmap(sucess2);

    //圆形按钮并且带有按下特效
    ui->pushButton->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);border:2px groove gray;border-radius:45px;padding:2px 4px;border-style: outset;}"
                                  "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                  "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}"
                                  );
    ui->pushButton->setText("");
    ui->pushButton->setIcon(QIcon("://res/checked.png"));
    ui->pushButton->setIconSize(QSize(84,84));


}
