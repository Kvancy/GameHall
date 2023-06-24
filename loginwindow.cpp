#include "loginwindow.h"
#include "qdatetime.h"
#include "smtp.h"
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
    ui->label_email->setStyleSheet("font: 10pt 'Arial';");
    ui->label_pwd->setStyleSheet("font: 10pt 'Arial';");
    ui->label_email->setStyleSheet("font: 10pt 'Arial';");
    ui->label_code->setStyleSheet("font: 10pt '黑体';");
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
    ui->get_email->setStyleSheet("font: 18 14pt '微软雅黑 Light';" //字体
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
    ui->get_code->setStyleSheet("font: 18 14pt '微软雅黑 Light';" //字体
                              "color: rgb(31,31,31);"		//字体颜色
                               "padding-left:20px;"       //内边距-字体缩进
                              "background-color: rgb(255, 255, 255);" //背景颜色
                              "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置
    ui->judge->setStyleSheet("color:rgb(255,0,0);"
                             "font: 10pt 'Arial'");
    ui->getuser->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9a-zA-Z]{1,10}")));


}

void LoginWindow::mybtn()
{
    connect(ui->signUp,&QPushButton::clicked,this,&LoginWindow::sign);
    MainWindow *m = new MainWindow();
    connect(ui->back,&QPushButton::clicked,[=](){
        m->show();
        close();});
    connect(ui->send,&QPushButton::clicked,this,&LoginWindow::send);
}

void LoginWindow::Close()
{
    close();
}

void LoginWindow::sign()
{
    QString user = ui->getuser->text();
    QString pwd = ui->getpwd->text();
    QString email = ui->get_email->text();
    QString code = ui->get_code->text();

    QString s = QString("select * from users where id='%1'").arg(user);
    QSqlQuery query;
    query.exec(s);
    QString s2 = QString("select * from users where email='%1'").arg(email);
    QSqlQuery query2;
    query2.exec(s2);
    if(user.isEmpty())
    {
        ui->judge->setText("Username Empty!");
        ui->judge->show();
        ui->gantanhao->move(490,140);
        ui->gantanhao->show();
    }
    else if(query.first())
    {
        ui->judge->setText("Username has been signed up!");
        ui->judge->show();
        ui->gantanhao->move(490,140);
        ui->gantanhao->show();
    }
    else if(query2.first())
    {
        ui->judge->setText("Email has been used!");
        ui->judge->show();
        ui->gantanhao->move(490,240);
        ui->gantanhao->show();
    }
    else if(pwd.isEmpty())
    {
        ui->judge->setText("PWD Empty!");
        ui->judge->show();
        ui->gantanhao->move(490,190);
        ui->gantanhao->show();
    }
    else if(email.isEmpty())
    {
        ui->judge->setText("Email Empty!");
        ui->judge->show();
        ui->gantanhao->move(490,240);
        ui->gantanhao->show();
    }
    else if(code.isEmpty())
    {
        ui->judge->setText("Code Empty!");
        ui->judge->show();
        ui->gantanhao->move(490,290);
        ui->gantanhao->show();
    }
    else
    {
        if(code.toInt()==verificationcode)
        {
            QByteArray pwdMD5 = QCryptographicHash::hash(pwd.toLocal8Bit(),QCryptographicHash::Md5).toHex();
            QString s2 = QString("INSERT INTO users (id,passwordMD5,`password`,email)VALUES ('%1','%2','%3','%4')").arg(user).arg(pwdMD5).arg(pwd).arg(email);
            QSqlQuery query2;
            query2.exec(s2);

            SignSucess *signsucess = new SignSucess();
            connect(signsucess,&SignSucess::Close,this,&LoginWindow::Close);
            signsucess->exec();
        }
        else
        {

            ui->judge->setText("Code wrong!");
            ui->judge->show();
            ui->gantanhao->move(490,280);
            ui->gantanhao->show();
        }
    }
}

void LoginWindow::send()
{
    //邮箱地址
    QString mailaddress_qstr = ui->get_email->text(); //获取用户输入的邮箱地址
    std::string mailaddress_str = mailaddress_qstr.toStdString();
    const char * mailaddress_c = mailaddress_str.c_str();
    //这里因为抄下来的代码是char * 类型的，所以我们需要转换一下
    //随机生成验证码
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    verificationcode = rand()%(99999 - 10000) + 10000;//产生一个5位数的随机数
    //将验证码加入字符串
    QString verificationcode_qstr = QString("验证码为%1，若非本人操作，请勿告诉他人。——————信息来自TeamProject").arg(verificationcode);
    std::string verificationcode_str = verificationcode_qstr.toStdString();
    const char * verificationcode_c = verificationcode_str.c_str();
    //登录邮箱
    Smtp smtp("1538629310@qq.com","vbeopifldxcjifci");  //第一个参数是发送者邮箱，第二个授权码，并不是邮箱密码
    //发送邮件
    smtp.send(mailaddress_c,"验证信息",verificationcode_c);

}
