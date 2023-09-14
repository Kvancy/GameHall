#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QCryptographicHash>
#include "roundimg.h"
#include "gamehall.h"
#include "signsucess.h"
#include <QRegularExpressionValidator>
#include <QSettings>
#include <QThreadPool>
#include <m_thread.h>
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
    database=QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("47.97.68.254");
    database.setPort(3306);
    database.setUserName("root");
    database.setPassword("root");
    database.setDatabaseName("myexe");
    database.open();
    if(!database.isOpen())
    {
        setWindowTitle("请联网后重新启动！");
        //exit(0);
    }
}

void MainWindow::login_init()//登录界面的美化
{
    ui->gantanhao->hide();

    pwdRemember();

    ui->judge->hide();

    ui->judge->setStyleSheet("color:rgb(255,0,0);"
                             "font: 10pt 'Arial'");

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
    QPixmap pixMap;
    img.load("://res/login.jpg");//图片加载
    pixMap= img.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//scaled用于缩放尺寸100为圆形的半径
    pixMap =  PixmapToRound(pixMap, 100);
    ui->label_img->setPixmap(pixMap);
    img.load("://res/login2.jpg");//左边皮卡丘捏
    pixMap= img.scaled(260,380, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_img2->setPixmap(pixMap);
    //上端圆形图片，用自己头像嘿嘿
    img.load(":/res/exclamation.png");//图片加载
    pixMap= img.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    pixMap =  PixmapToRound(pixMap, 20);
    ui->gantanhao->setPixmap(pixMap);
    //规定输入规范
    ui->lineEdit_1->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9a-zA-Z]{1,10}")));   //只能输入数字字母,控制不超过10位
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
        //记住账号
        QSettings writeini(inipath,QSettings::IniFormat);//inipath如果没有指定文件则创造新的文件
        writeini.setValue("Login/username",username);
        writeini.setValue("Login/isremember","false");
        if(ischecked)//登录成功并选中记住密码时更新ini配置
        {
            QString password = ui->lineEdit_2->text();
            writeini.setValue("Login/password",password);
            writeini.setValue("Login/isremember","true");
        }
        //试图优化登录是服务器验证过程假死界面
//        Wating1 *wt = new Wating1(this);
//        wt->show();
//        wt->m_move->start();
//        QCoreApplication::processEvents();
        GameHall* gamehall = new GameHall(username);
//        QCoreApplication::processEvents();
        connect(gamehall,&GameHall::m_show,this,&MainWindow::Show);
//        创建新线程处理gamehall的生成（还是挺费时的）
//        thread1 *thred = new thread1;
//        thred->Setmainw(this);
//        thred->GetUsername(username);
//        QThreadPool::globalInstance()->start(thred);
//        connect(thred,&thread1::runout,this,[=](GameHall* gamehall){
//            connect(gamehall,&GameHall::m_show,this,&MainWindow::Show);
//            gamehall->show();
//            delete wt;
//            close();
//        });
//        connect(this,&MainWindow::stop,thred,
        gamehall->show();
        close();


    }
    else if(flag==1)//用户名错误
    {
        ui->gantanhao->move(480,162);
        ui->gantanhao->show();
        ui->judge->setText("未找到该用户！");
        ui->judge->show();
    }
    else//密码错误
    {

        ui->gantanhao->move(480,222);
        ui->gantanhao->show();
        ui->judge->setText("密码错误！");
        ui->judge->show();
    }
}

void MainWindow::signDown()//注册按钮按下
{
    LoginWindow *login = new LoginWindow();
    connect(login,&LoginWindow::mainwindow_show,this,&MainWindow::Show);
    login->show();
    close();
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

void MainWindow::Show()
{
    show();
}

void MainWindow::checkbox_checked()//按钮状态改变及时更新判断数据
{
    ischecked = ui->checkBox->isChecked();
}


