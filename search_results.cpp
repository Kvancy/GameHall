#include "search_results.h"
#include "hallbtn.h"
#include "qlabel.h"
#include "qprocess.h"
#include "ui_search_results.h"

Search_results::Search_results(QStringList dic,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search_results)
{
    ui->setupUi(this);
    QStringList icon_path;
    icon_path << ":/res/fiveline.png" << ":/res/guess.jpg" << ":/res/Tabletennis.png" << ":/res/landlord.png"
         << ":/res/ayqj.png" << ":/res/chuanqi.png" << ":/res/lol.jpg" << ":/res/sha.jpg";
    QStringList exe_path;
    exe_path << "/games/five2line/five2line.exe" << "/games/onlineChat/chat.exe";
    enum Game
    {
        五子棋 = 0 ,
        你画我猜,
        腾讯桌球,
        欢乐斗地主,
        暗夜奇迹,
        传奇,
        英雄联盟,
        三国杀
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
        if(dic[i]=="五子棋")
        {
            game = 五子棋;
        }
        else if(dic[i]=="你画我猜")
        {
            game = 你画我猜;
        }
        else if(dic[i]=="腾讯桌球")
        {
            game = 腾讯桌球;
        }
        else if(dic[i]=="欢乐斗地主")
        {
            game = 欢乐斗地主;
        }
        else if(dic[i]=="暗夜奇迹")
        {
            game = 暗夜奇迹;
        }
        else if(dic[i]=="传奇")
        {
            game = 传奇;
        }
        else if(dic[i]=="英雄联盟")
        {
            game = 英雄联盟;
        }
        else if(dic[i]=="三国杀")
        {
            game = 三国杀;
        }

        if(i%4==0)
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
