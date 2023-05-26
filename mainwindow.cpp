#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "loginwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QCryptographicHash>
#include "roundimg.h"
#include "gamehall.h"
#include <QRegularExpressionValidator>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    this->setWindowOpacity(0.7);//设置透明1-全体透明

    setWindowTitle("快快登录开始游戏吧嘿嘿");
    setWindowIcon(QIcon(":/res/R-C.png"));
    linkDatabase();
    login_init();
    mybtn();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::linkDatabase()//连接数据库
{
    qDebug() << QSqlDatabase::drivers();
    database=QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("rm-cn-wwo38fhvh0001iuo.rwlb.rds.aliyuncs.com");
    database.setPort(3306);
    database.setUserName("root");
    database.setPassword("Ren123!@");
    database.setDatabaseName("myexe");
    database.open();
    if(!database.isOpen())
    {
        setWindowTitle("数据库没有连接成功呐！");
        //exit(0);
    }
}

void MainWindow::login_init()//登录界面的美化
{
    ui->gantanhao->hide();

    pwdRemember();

    ui->undoView->setStyleSheet("background-color: rgb(255,255,255);");
    ui->widget->setStyleSheet("background-color: rgb(255,255,255);");
    ui->signup->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                              "border: none;border-radius:5px;}"
                              "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                              "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->login->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                             "border: none;border-radius:5px;}"
                             "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                             "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->lineEdit_1->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                  "color: rgb(31,31,31);"		//字体颜色
                                  "padding-left:20px;"       //内边距-字体缩进
                                  "background-color: rgb(255, 255, 255);" //背景颜色
                                  "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置
    ui->lineEdit_2->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                  "color: rgb(31,31,31);"		//字体颜色
                                  "padding-left:20px;"       //内边距-字体缩进
                                  "background-color: rgb(255, 255, 255);" //背景颜色
                                  "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置
    ui->label_img->setStyleSheet("background-color: rgb(255, 255, 255);"
                                 "border-radius:15px;");
    ui->label_img2->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->usernames->setStyleSheet("font: 10pt 'Arial';");
    ui->pwd->setStyleSheet("font: 10pt 'Arial';");
    ui->havenot->setStyleSheet("font: 10pt 'Arial';");


    QPixmap img;//上端圆形图片，用自己头像嘿嘿
    img.load("://res/login.jpg");//图片加载
    QPixmap pixMap= img.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //50为圆形的半径
    pixMap =  PixmapToRound(pixMap, 100);
    ui->label_img->setPixmap(pixMap);

    QPixmap img2;//左边皮卡丘捏
    img2.load("://res/login2.jpg");
    QPixmap pixMap2= img2.scaled(260,380, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_img2->setPixmap(pixMap2);

    QPixmap gth;//上端圆形图片，用自己头像嘿嘿
    gth.load(":/res/exclamation.png");//图片加载
    QPixmap gth2= gth.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //50为圆形的半径
    gth2 =  PixmapToRound(gth2, 20);
    ui->gantanhao->setPixmap(gth2);

    //规定输入规范
    ui->lineEdit_1->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{1,10}")));   //只能输入数字,控制不超过10位
}

int MainWindow::check()//MD5检验账号密码
{
    QString id = ui->lineEdit_1->text();
    QString pwd = ui->lineEdit_2->text();
    QSqlQuery query;
    QString s = QString("select * from users where id='%1'").arg(id);
    query.exec(s);
    if(!query.first()||id.isEmpty())//没找到用户名
    {
        return 1;
    }
    else
    {
        QString s = QString("select passwordMD5 from users where id='%1'").arg(id);
        query.exec(s);
        if(query.first())//找到用户名后核对密码
        {
            //插入花指令增加逆向破解难度
            __asm__("test $0,%eax\n"
                    "jz label\n"
                    "add $0xff,%esp\n"
                    ".byte 0xe8,0x80,0x80,0x80\n"
                    "label:\n"
                    );
            QByteArray Tpwd = query.value(0).toByteArray();//数据库对应密码
            QByteArray Bpwd = pwd.toLocal8Bit();//转类型
            QByteArray pwdMd5 = QCryptographicHash::hash(Bpwd,QCryptographicHash::Md5).toHex();//md5
            if(Tpwd==pwdMd5)
            {
                return 0;
            }
            else
            {
                return 2;
            }
        }
    }
}

void MainWindow::login_judge()//根据判断结果显示不同内容
{
    int flag = check();
    int x = 261;int y= 254;//错误提示显示坐标

    if(flag==0)//登录成功
    {
        QString username = ui->lineEdit_1->text();
        QSettings writeini(inipath,QSettings::IniFormat);
        writeini.setValue("Login/username",username);
        qDebug() << writeini.value("Login/username");
        writeini.setValue("Login/isremember","false");
        if(ischecked)//登录成功并选中记住密码时更新ini配置
        {
            QString password = ui->lineEdit_2->text();
            writeini.setValue("Login/password",password);
            writeini.setValue("Login/isremember","true");
        }
        GameHall *gamehall = new GameHall();
        gamehall->show();
        close();
    }
    else if(flag==1)//用户名错误
    {
        ui->gantanhao->move(480,162);
        ui->gantanhao->show();
    }
    else//密码错误
    {

        ui->gantanhao->move(480,222);
        ui->gantanhao->show();
    }
}

void MainWindow::signDown()//注册按钮按下
{
    close();
    LoginWindow *login = new LoginWindow();
    login->show();
}

void MainWindow::mybtn()
{
    connect(ui->login,&QPushButton::clicked,this,&MainWindow::login_judge);
    connect(ui->signup,&QPushButton::clicked,this,&MainWindow::signDown);
    connect(ui->checkBox,&QPushButton::clicked,this,&MainWindow::checkbox_checked);
}

void MainWindow::pwdRemember()
{
    QSettings setting(inipath,QSettings::IniFormat);
    QString isremember = setting.value("Login/isremember").toString();
    QString username = setting.value("Login/username").toString();
    QString password = setting.value("Login/password").toString();
    ui->lineEdit_1->setText(username);
    if(isremember == "true")
    {
        ui->lineEdit_2->setText(password);
        ui->checkBox->setChecked(true);
        ischecked = true;
    }
    else
    {
        ui->checkBox->setChecked(false);
        ischecked = false;
    }
}

void MainWindow::checkbox_checked()//按钮状态改变及时更新判断数据
{
    ischecked = ui->checkBox->isChecked();
}
