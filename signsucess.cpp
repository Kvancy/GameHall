#include "signsucess.h"
#include "qmovie.h"
#include "qsqlquery.h"
#include "qtimer.h"
#include "roundimg.h"
#include "ui_download.h"
#include "ui_loginwindow.h"
#include "ui_signsucess.h"
#include <QPixmap>
#include <QPushButton>
#include "mainwindow.h"
#include "ui_removey.h"
#include "hallbtn.h"
#include "qprocess.h"
#include "ui_search_results.h"
Wating1::Wating1(QWidget *parent) :
    QLabel(parent)
{   //等待的gif类QLabel
    this->setGeometry(210,180,50,50);//设置位置和大小，我的窗口是800*480,所以我设这么大
    this->setAlignment(Qt::AlignCenter);//设置字体上下左右BABA居中咯（这里很重要,是你的动图在lable的位置）
    this->setStyleSheet("background:dark");//这个很重要，这个叫背景颜色透明（当然动图背景也要选透明的）
    m_move = new QMovie(":/res/wating3.gif");//写上你的图片路径，我这里是用了资源
    m_move->setScaledSize(QSize(50,50));//设置动图大小咯，想多大就多大，只要你的lable放得下
    this->setMovie(m_move);//把你的move放进去lable里面
}

Wating1::~Wating1()
{
}


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
                MainWindow *m = new MainWindow();
                m->show();
                delete this;
            });

}

SignSucess::~SignSucess()
{
    delete ui;
}
removeY::removeY(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::removeY)
{
    ui->setupUi(this);
    connect(ui->OK,&QPushButton::clicked,[=]()
            {
                this->hide();
            });
    setWindowIcon(QIcon(":/res/R-C.png"));
    setWindowTitle("卸载成功！");
}

removeY::~removeY()
{
    delete ui;
}

Search_results::Search_results(QStringList dic,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search_results)
{
    ui->setupUi(this);
    QStringList icon_path;
    icon_path << ":/res/fiveline.png" << ":/res/guess.jpg" << ":/res/zmxy.png" << ":/res/sjsj.png"
              << ":/res/Warrior.jpg" << ":/res/chuanqi.png" << ":/res/lol.jpg" << ":/res/sha.jpg" << ":/res/landlord.png"
              << ":/res/ayqj.png" << ":/res/Tabletennis.png";
    QStringList exe_path;
    exe_path << "/games/five2line/five2line.exe" << "/games/onlineChat/chat.exe" << "/games/Zmxyol/zmxy_online.exe"
             << "/games/sjsj.exe" << "/games/yzzr/yzzr.exe";
    QStringList game_name;
    game_name <<"五子棋" <<"你画我猜"<< "造梦西游"<<"神将世界"<< "勇者之刃"<< "传奇"<<"英雄联盟"<< "三国杀"<< "欢乐斗地主"<<"暗夜奇迹"<<"腾讯桌球";
        enum Game
        {
            五子棋 = 0 ,
                你画我猜,
            造梦西游,
            神将世界,
            勇者之刃,
            传奇,
                英雄联盟,
            三国杀,
            欢乐斗地主,
                暗夜奇迹,
            腾讯桌球,

        }game;

    if(dic.empty())
    {
        QPixmap img;
        img.load(":/res/cantfind.png");
        QPixmap pixMap= img.scaled(550,90, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QLabel *no_find= new QLabel(this);
        no_find->setGeometry(30,30,550,90);
        no_find->setPixmap(pixMap);
    }
    //按照搜索得到的结果绘制按钮
    else
    {
        for(int i=0;i<dic.length();i++)
        {
            HallBtn *btn = new HallBtn(this);
            QString game_path;
            switch(game_name.indexOf(dic[i]))
            {
            case 0:
                game = 五子棋;
                    break;
            case 1:
                game = 你画我猜;
                    break;
            case 2:
                game = 造梦西游;
                    break;
            case 3:
                game = 神将世界;
                    break;
            case 4:
                game = 勇者之刃;
                    break;
            case 5:
                game = 传奇;
                    break;
            case 6:
                game = 英雄联盟;
                    break;
            case 7:
                game = 三国杀;
                    break;
            case 8:
                game = 欢乐斗地主;
                    break;
            case 9:
                game = 暗夜奇迹;
                    break;
            default:
                game = 腾讯桌球;
                    break;
            }
            if(i%4==0)//为按钮换行，每四个换一行
            {
                btn->move(50,10+140*(i/4));
                btn->setIcon(QIcon(icon_path[game]));
                btn->setIconSize(QSize(80,90));
                btn->setStyleSheet("QToolButton{border-style: flat;}");
                connect(btn,&QToolButton::clicked,[=]()
                        {
                            QProcess process(this);
                            process.startDetached(globalpath+exe_path[game]);
                        });
                btn->show();

            }
            else
            {
                btn->move(50+150*(i%4),10+140*(i/4));
                btn->setIcon(QIcon(icon_path[game]));
                btn->setIconSize(QSize(80,90));
                btn->setStyleSheet("QToolButton{border-style: flat;}");
                connect(btn,&QToolButton::clicked,[=]()
                        {
                            QProcess process(this);
                            process.startDetached(globalpath+exe_path[game]);
                        });
                btn->show();
            }
        }
    }
}

Search_results::~Search_results()
{
    delete ui;
}

Download::Download(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Download)
{
    ui->setupUi(this);
    setWindowTitle("下载游戏吧");
    connect(ui->stop,&QPushButton::clicked,[=](){
        this->hide();
    });
    setWindowIcon(QIcon(":/res/R-C.png"));
    ui->stop->setEnabled(false);
    ui->stop->setStyleSheet("QPushButton{background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0,"
                            "stop:0.0112994 rgba(64, 145, 252, 255),stop:1 rgba(255, 255, 255, 255));"
                            "color: rgb(255, 255, 255);"
                            "border:0px groove gray;border-radius:7px;padding:2px 4px;"
                            "font: 10pt 'Candara';}"
                            "QPushButton:hover{background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0,"
                            "stop:0.0112994 rgba(66, 175, 255, 255),stop:1 rgba(255, 255, 255, 255))};");
    ui->stop->setCursor(Qt::PointingHandCursor);
}

Download::~Download()

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
    connect(ui->back,&QPushButton::clicked,[=](){
        emit mainwindow_show();
        delete this;
    });
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
    //随机生成验证码
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    verificationcode = rand()%(99999 - 10000) + 10000;//产生一个5位数的随机数
    //将验证码加入字符串
    QString verificationcode_qstr = QString("验证码为%1，请不要把验证码泄露给其他人,若非本人操作，请忽略此条邮件。——————信息来自TeamProject").arg(verificationcode);
    std::string verificationcode_str = verificationcode_qstr.toStdString();
    const char * verificationcode_c = verificationcode_str.c_str();
    //登录邮箱
      //第一个参数是发送者邮箱，第二个授权码
    //发送邮件

    if(mailaddress_qstr.length()>10)
    {
        if(mailaddress_qstr.endsWith("@qq.com"))
        {
                Smtp smtp("1538629310@qq.com","vbeopifldxcjifci");
                smtp.send(mailaddress_c,"验证信息",verificationcode_c);
                disconnect(ui->send,&QPushButton::clicked,this,&LoginWindow::send);
                ui->send->setCursor(Qt::ArrowCursor);
                QTimer *timer = new QTimer(this);//60秒断开连接
                timer->start(60000);
                connect(timer,&QTimer::timeout,[=]()
                        {
                    connect(ui->send,&QPushButton::clicked,this,&LoginWindow::send);
                    ui->send->setCursor(Qt::PointingHandCursor);
                });
                QTimer *timer2 = new QTimer(this);//60秒倒计时
                int text = 60;
                timer2->start(1000);
                connect(timer2,&QTimer::timeout,[=]()mutable
                        {
                    if(text!=0)
                        {
                        text-=1;
                        ui->send->setText("已发送: "+QString::number(text,10));
                    }
                    else
                        {
                        ui->send->setText("重新发送");
                        text=60;
                        timer2->stop();
                    }
                });
        }
        else
        {
        ui->judge->setText("Not qq email!");
        ui->judge->show();
        }
    }
    else
    {
        ui->judge->setText("Email not found!");
        ui->judge->show();
    }


}


void SignSucess::init()
{
    QPixmap WA;
    WA.load(":/res/WA.jpg");
    WA= WA.scaled(221,331, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->WA->setPixmap(WA);
    WA.load("://res/sucess.png");
    WA= WA.scaled(221,61, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->sucess->setPixmap(WA);
    //圆形按钮并且带有按下特效
    ui->pushButton->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);border:2px groove gray;border-radius:45px;padding:2px 4px;border-style: outset;}"
                                  "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                  "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}"
                                  );
    ui->pushButton->setText("");
    ui->pushButton->setIcon(QIcon("://res/checked.png"));
    ui->pushButton->setIconSize(QSize(84,84));


}


void Download::sltProgress(qint64 bytesRead, qint64 totalBytes, qreal progress)
{
    ui->progressBar->setValue(progress*100);
    ui->progressBar->setFormat(QString::number(progress*100, 'f', 2) + "%");
}
void Download::sltDownloadFinished()
{
    ui->stop->setText(tr("下载完成"));
    ui->stop->setEnabled(true);

}
