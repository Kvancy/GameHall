#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QCryptographicHash>
#include "roundimg.h"
#include "mainwindow.h"
#include "signsucess.h"
LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowTitle("快快注册吧嘿嘿");
    setWindowIcon(QIcon(":/res/R-C2.jpg"));
    sign_init();
    mybtn();
    ui->judge->hide();
    ui->gantanhao->hide();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::sign_init()
{

    QPixmap img;
    img.load("://res/signup.png");
    QPixmap pixMap= img.scaled(260,380, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap welcome;
    welcome.load(":/res/welcome.png");
    QPixmap welcome2= welcome.scaled(223,93, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap gth;//上端圆形图片，用自己头像嘿嘿
    gth.load(":/res/exclamation.png");//图片加载
    QPixmap gth2= gth.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //50为圆形的半径
    gth2 =  PixmapToRound(gth2, 20);
    ui->gantanhao->setPixmap(gth2);
    ui->labei_img->setPixmap(pixMap);
    ui->label_wcm->setPixmap(welcome2);
    ui->label_name->setStyleSheet("font: 10pt 'Arial';");
    ui->label_pwd->setStyleSheet("font: 10pt 'Arial';");
    ui->label_name->setStyleSheet("font: 10pt 'Arial';");
    ui->signUp->setStyleSheet("QPushButton{background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0,"
                              "stop:0.0112994 rgba(64, 145, 252, 255),stop:1 rgba(255, 255, 255, 255));"
                              "color: rgb(255, 255, 255);"
                              "border:0px groove gray;border-radius:7px;padding:2px 4px;"
                              "font: 10pt 'Candara';}"
                              "QPushButton:hover{background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0,"
                              "stop:0.0112994 rgba(66, 175, 255, 255),stop:1 rgba(255, 255, 255, 255))};");
    ui->back->setStyleSheet("QPushButton{background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0,"
                            "stop:0.0112994 rgba(64, 145, 252, 255),stop:1 rgba(255, 255, 255, 255));"
                            "color: rgb(255, 255, 255);"
                            "border:0px groove gray;border-radius:7px;padding:2px 4px;"
                            "font: 10pt 'Candara';}"
                            "QPushButton:hover{background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0,"
                            "stop:0.0112994 rgba(66, 175, 255, 255),stop:1 rgba(255, 255, 255, 255))};");
    ui->undoView->setStyleSheet("background-color: rgb(255,255,255);");
    ui->getname->setStyleSheet("font: 18 14pt '微软雅黑 Light';" //字体
                                  "color: rgb(31,31,31);"		//字体颜色
                                  "padding-left:20px;"       //内边距-字体缩进
                                  "background-color: rgb(255, 255, 255);" //背景颜色
                                  "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置
    ui->getuser->setStyleSheet("font: 18 14pt '微软雅黑 Light';" //字体
                               "color: rgb(31,31,31);"		//字体颜色
                               "padding-left:20px;"       //内边距-字体缩进
                               "background-color: rgb(255, 255, 255);" //背景颜色
                               "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置
    ui->getpwd->setStyleSheet("font: 18 14pt '微软雅黑 Light';" //字体
                               "color: rgb(31,31,31);"		//字体颜色
                               "padding-left:20px;"       //内边距-字体缩进
                               "background-color: rgb(255, 255, 255);" //背景颜色
                               "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置
    ui->judge->setStyleSheet("color:rgb(255,0,0);"
                             "font: 10pt 'Arial'");


}

void LoginWindow::mybtn()
{
    connect(ui->signUp,&QPushButton::clicked,this,&LoginWindow::sign);
    connect(ui->back,&QPushButton::clicked,[=](){
        MainWindow *m = new MainWindow();
        m->show();close();});
}

void LoginWindow::Close()
{
    close();
}

void LoginWindow::sign()
{
    QString user = ui->getuser->text();
    QString pwd = ui->getpwd->text();
    QString name = ui->getname->text();
    QString s = QString("select * from users where id='%1'").arg(user);
    QSqlQuery query;
    query.exec(s);
    if(user.isEmpty())
    {
        qDebug() << "The user name, password and name cannot be empty!";
        ui->gantanhao->move(490,180);
        ui->gantanhao->show();
    }
    else if(query.first())
    {
        qDebug() << "The user name has been registered,try again?";
        ui->judge->setText("The user name has been registered !");
        ui->judge->show();
        ui->gantanhao->move(490,180);
        ui->gantanhao->show();
    }
    else if(pwd.isEmpty())
    {
        ui->gantanhao->move(490,230);
        ui->gantanhao->show();
    }
    else if(name.isEmpty())
    {
        ui->gantanhao->move(490,280);
        ui->gantanhao->show();
    }
    else
    {
        qDebug() << "Successful registration！";
        QByteArray pwdMD5 = QCryptographicHash::hash(pwd.toLocal8Bit(),QCryptographicHash::Md5).toHex();
        QString s2 = QString("INSERT INTO users (id,passwordMD5,`password`,name)VALUES ('%1','%2','%3','%4')").arg(user).arg(pwdMD5).arg(pwd).arg(name);
        QSqlQuery query2;
        query.exec(s2);

        SignSucess *signsucess = new SignSucess();
        connect(signsucess,&SignSucess::Close,this,&LoginWindow::Close);
        signsucess->exec();

    }
}
