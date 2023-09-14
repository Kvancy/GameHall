#include "gamehall.h"
#include "ui_gamehall.h"
#include <QProcess>
#include <QMovie>
#include <QCompleter>
#include <QWheelEvent>
#include <QBuffer>
#include <QFileDialog>
#include "roundimg.h"
#include <QSqlQuery>
#include <QMenu>
#include <QNetworkReply>
#include <mainwindow.h>
#include "signsucess.h"
GameHall::GameHall(QString id,QWidget *parent) ://id记录登录用户的用户id
    QWidget(parent),
    ui(new Ui::GameHall)
{
    ui->setupUi(this);
    setWindowTitle("Game Hall!");
    setMouseTracking(true);
    setWindowIcon(QIcon(":/res/R-C.png"));
    ID = id;
    GameName<<"fiveline"<<"chat"<<"zmxy"<<"sjsj"<<"yzzr";
    GameFile<<"/games/five2line"<<"/games/five2line"<<"/games/Zmxyol"<<"/games/sjsj"<<"/games/yzzr";
    exe_path<<"/games/five2line/five2line.exe" << "/games/onlineChat/chat.exe" << "/games/Zmxyol/zmxy_online.exe"
             << "/games/sjsj.exe" << "/games/yzzr/yzzr.exe";
    DownPath<<"https://desktop.docker.com/win/main/amd64/Docker%20Desktop%20Installer.exe"
             <<"https://desktop.docker.com/win/main/amd64/Docker%20Desktop%20Installer.exe"
             <<"http://video.5054399.com/microgame/4399zmxyonline.exe?from=zmxyblockflashtip&1678844298"
             <<"https://webpic.my4399.com/re/packer/sjsj/4399/3000_2/%E7%A5%9E%E5%B0%86%E4%B8%96%E7%95%8C.exe"
             <<"https://video.5054399.com/microgame/4399yzzr.exe?from=yzzrblockflashtip";

    //设置gif播放
    HallBtn *sender[5] = {ui->fiveline,ui->chat,ui->zmxy,ui->sjsj,ui->yzzr};
    QMovie *movie = new QMovie;
    movie->setParent(this);
    movie->setFileName(path_gif[index]);
    movie->setScaledSize(QSize(ui->gif->width(),(ui->gif->height())));
    ui->gif->setMovie(movie);
    movie->start();

    setMouseTracking(true);
    init();
    btncon(movie,ui->gif,sender);

    search();
    //利用事件过滤器给搜索label添加点击释放信号功能
    ui->searchIcon->installEventFilter(this);


}

GameHall::~GameHall()
{
    delete ui;
}

void GameHall::init()
{
//    ui->left->hide();
//    ui->right->hide();
    //加载左右移图片
    ui->left->setText("");
    ui->left->setIcon(QIcon(":/res/left.png"));
    ui->left->setIconSize(QSize(85,85));
    ui->right->setText("");
    ui->right->setIcon(QIcon(":/res/right.png"));
    ui->right->setIconSize(QSize(85,85));
    ui->left->setStyleSheet("QPushButton{border-radius:35px;}"
                             "QPushButton:pressed{background-color:rgb(204, 228, 247);}"
                             );

    ui->right->setStyleSheet("QPushButton{border-radius:35px;}"
                            "QPushButton:pressed{background-color:rgb(204, 228, 247);}"
                            );
    //设置游戏图标的图像
    ui->fiveline->setIcon(QIcon(":/res/fiveline.png"));
    ui->fiveline->setIconSize(QSize(ui->fiveline->width()-10,ui->fiveline->height()-10));
    ui->fiveline->setStyleSheet("QToolButton{border-style: flat;}");

    ui->chat->setIcon(QIcon(":/res/guess.jpg"));
    ui->chat->setIconSize(QSize(ui->fiveline->width()-10,ui->fiveline->height()-10));
    ui->chat->setStyleSheet("QToolButton{border-style: flat;}");

    ui->zmxy->setIcon(QIcon(":/res/zmxy.png"));
    ui->zmxy->setIconSize(QSize(ui->fiveline->width()-10,ui->fiveline->height()-10));
    ui->zmxy->setStyleSheet("QToolButton{border-style: flat;}");

    ui->sjsj->setIcon(QIcon(":/res/sjsj.png"));
    ui->sjsj->setIconSize(QSize(ui->fiveline->width()-10,ui->fiveline->height()-10));
    ui->sjsj->setStyleSheet("QToolButton{border-style: flat;}");

    ui->yzzr->setIcon(QIcon(":/res/Warrior.jpg"));
    ui->yzzr->setIconSize(QSize(ui->fiveline->width()-10,ui->fiveline->height()-10));
    ui->yzzr->setStyleSheet("QToolButton{border-style: flat;}");

    ui->chuanqi->setIcon(QIcon(":/res/chuanqi.png"));
    ui->chuanqi->setIconSize(QSize(ui->fiveline->width()-10,ui->fiveline->height()-10));
    ui->chuanqi->setStyleSheet("QToolButton{border-style: flat;}");

    ui->lol->setIcon(QIcon(":/res/lol.jpg"));
    ui->lol->setIconSize(QSize(ui->fiveline->width()-10,ui->fiveline->height()-10));
    ui->lol->setStyleSheet("QToolButton{border-style: flat;background-color: rgb(255, 255, 255);}");

    ui->sgs->setIcon(QIcon(":/res/sha.jpg"));
    ui->sgs->setIconSize(QSize(ui->fiveline->width()-10,ui->fiveline->height()-10));
    ui->sgs->setStyleSheet("QToolButton{border-style: flat;}");

    //搜索框设置
    ui->searchEdit->setStyleSheet("font: 25 10pt '楷书 Light';" //字体
                                  "color: rgb(31,31,31);"		//字体颜色
                                  "padding-left:10px;"       //内边距-字体缩进
                                  "background-color: rgb(255, 255, 255);" //背景颜色
                                  "border:2px solid rgb(20,196,188);border-radius:20px;");//边框粗细-颜色-圆角
    //Home按钮
    ui->Home->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);border:2px groove gray;border-radius:40px;padding:2px 4px;border-style: outset;}"
                            "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                            "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");

    ui->exit->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);border:2px groove gray;border-radius:40px;padding:2px 4px;border-style: outset;}"
                            "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                            "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    //搜索图标
    QPixmap img;
    img.load(":/res/search.png");
    QPixmap pixMap= img.scaled(41,41, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->searchIcon->setPixmap(pixMap);

    img.load(":/res/rank.png");
    pixMap= img.scaled(221,41, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->rank->setPixmap(pixMap);

    //查询是否上传过头像    
    QSqlQuery query;
    QString s = QString("select avatar from users where id='%1'").arg(ID);
    query.exec(s);
    if(query.first())
    {
        if(query.value(0)==1)
        {
            //曾经上传过头像
            QSqlQuery query3;
            QPixmap img;
            query.exec(QString("select imagedata,format from users where id='%1'").arg(ID));
            query.first();
            //查询数据库记载的图像类型
            char *format = query.value(1).toString().toLatin1().data();
            img.loadFromData(query.value(0).toByteArray(),format);
            img= img.scaled(70,70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            //70为圆形的直径
            img = PixmapToRound(img, 70);
            ui->avatar->setPixmap(img);
        }
    }

}

void GameHall::btncon(QMovie *movie,QLabel *gif,HallBtn** btn)
{
    //左键按下时，没有游戏文件则下载游戏，有则启动游
    for(int i=0;i<GameFile.length();i++)
    {
        connect(btn[i],&QPushButton::clicked,[=]()
                {
                    if(QDir(path+GameFile[i]).exists())
                    {
                        QProcess *process = new QProcess(this);
                        process->start(path+exe_path[i]);
                        connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished(int, QProcess::ExitStatus)));
                        this->hide();
                        qDebug() << process->state();
                    }
                    else
                    {
                        Download *download = new Download();
                        DownloadTool *dt;
                        dt = new DownloadTool(DownPath[i], path + GameFile[i]);
                        connect(dt,SIGNAL(sigProgress(qint64, qint64, qreal)),download,SLOT(sltProgress(qint64, qint64, qreal)));
                        connect(dt,SIGNAL(sigDownloadFinished()),download,SLOT(sltDownloadFinished()));
                        download->show();
                        dt->startDownload();
                    }
                });
    }
    //对ranklabel（按下，游戏启动）设置游戏大厅的隐藏和显示
    connect(ui->label_2,&rankLbabel::Toshow,[=]()
            {
        this->show();
    });
    connect(ui->label_2,&rankLbabel::Tohide,[=]()
            {
        this->hide();
    });

    //为hallbtn添加右键菜单功能
    connect(ui->fiveline,SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
    connect(ui->chat,SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
    connect(ui->zmxy,SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
    connect(ui->sjsj,SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
    connect(ui->yzzr,SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));

    connect(ui->right,&QPushButton::clicked,[=]()
            {
                if(index==2)index=-1;
                index+=1;
                movie->stop();
                movie->setFileName(path_gif[index]);
                movie->start();
            });
    connect(ui->left,&QPushButton::clicked,[=]()
            {
                if(index==0)index=3;
                index-=1;
                movie->stop();
                movie->setFileName(path_gif[index]);
                movie->start();
            });
    connect(movie, &QMovie::frameChanged, [=](int frameNumber) {
        // GIF 动画执行三次播放下一个
        static int flag=1;
        if (frameNumber == movie->frameCount() - 1) {
            if(flag==3){
            movie->stop();
            if(index==2)index=-1;
            index+=1;
            movie->setFileName(path_gif[index]);
            movie->start();
            flag=1;
            }
            flag++;
        }});
    //移动滚动条效果
    connect(ui->verticalScrollBar,SIGNAL(valueChanged(int)),this,SLOT(slots_scroolwidget(int)));
    //头像上传按钮
    connect(ui->upload,&QPushButton::clicked,this,&GameHall::avatarUpload);

    connect(ui->exit,&QPushButton::clicked,[=]()
{
        emit m_show();
        this->deleteLater();
    });
}

void GameHall::search()
{
    QStringList dic;
    QSqlQuery query;
    QString s="SELECT games from games";
    query.exec(s);
    if(query.first())
    {
        dic<<query.value(0).toString();
        while(query.next())
        {
            dic<<query.value(0).toString();
        }
    }
    QCompleter *completer = new QCompleter(dic,this);
    completer->setFilterMode(Qt::MatchContains);
    ui->searchEdit->setCompleter(completer);
}

void GameHall::slots_scroolwidget(int value)
{
    double p=static_cast<double>(value)/static_cast<double>(ui->verticalScrollBar->maximum());
    //30是wiget横坐标，800是wigit的底y坐标-窗口的高度，+20是为了防止窗口y坐标到全局0
    ui->hall->move(20,-(ui->hall->height()-800)*p+20);


}
//重载鼠标滚轮来进行滚屏
void GameHall::wheelEvent(QWheelEvent *event)
{
    int para=event->angleDelta().y();//获得鼠标滚轮的滚动距离para，para<0向下滚动，>0向上滚动
    if (para<0)
    {
        //向下滚动，设定鼠标滚轮每滚动一个单位，滑块就移动20个单位
        //加入此判断的理由是，若当时滑块处于90的位置上，一旦继续下滑20个单位，就会超过最大范围100，show界面就会移动超出范围。
        if (ui->verticalScrollBar->value()+20<=100)
        {
            //发射verticalScrollBar的信号valueChange（value+20），连接到了我们之前写的slot_ScrollWidget(int)槽上
            emit ui->verticalScrollBar->valueChanged(ui->verticalScrollBar->value()+20);
                //设定滚动之后的滑块位置
                ui->verticalScrollBar->setSliderPosition(ui->verticalScrollBar->value()+20);
        }
        else
        {
            emit ui->verticalScrollBar->valueChanged(ui->verticalScrollBar->maximum());
            ui->verticalScrollBar->setSliderPosition(ui->verticalScrollBar->maximum());
        }
    }
    else
    {
        //向上滚动
        if (ui->verticalScrollBar->value()-20>=0)
        {
            emit ui->verticalScrollBar->valueChanged(ui->verticalScrollBar->value()-20);
            ui->verticalScrollBar->setSliderPosition(ui->verticalScrollBar->value()-20);
        }
        else
        {
            emit ui->verticalScrollBar->valueChanged(ui->verticalScrollBar->minimum());
            ui->verticalScrollBar->setSliderPosition(ui->verticalScrollBar->minimum());
        }
    }
}

void GameHall::avatarUpload()//头像上传
{
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("open image file"),
        "./", tr("Image files(*.png *.jpg)"));
    //设置缓冲区保存二进制
    if(fileName!="")
    {
        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);
        //打开并读取文件
        QFile *file = new QFile(fileName);
        file->open(QIODevice::ReadOnly);
        QByteArray data;
        data = file->readAll();
        //获取图片类型
        QFileInfo info(fileName);
        char* format = info.suffix().toUpper().toLatin1().data();
        //及时关闭文件
        file->close();
        QPixmap photo;
        photo.loadFromData(data, format);
        QPixmap pixMap= photo.scaled(70,70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        //70为圆形的直径
        pixMap =  PixmapToRound(pixMap, 70);
        ui->avatar->setPixmap(pixMap);

        QString s2 = QString("UPDATE users set imagedata=?,avatar='1',format='%2' WHERE id='%1';").arg(ID).arg(format);
        QSqlQuery query2;
        query2.prepare(s2);
        //好像不能直接用arg去传入，用addBindValue
        query2.addBindValue(data);
        query2.exec();
    }

}

bool GameHall::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==ui->searchIcon)
    {
        if(event->type()==QEvent::MouseButtonPress)
        {
            //搜索label点击后
            QStringList dic;
            int row=0;
            while(ui->searchEdit->completer()->setCurrentRow(row))
            {
                dic << ui->searchEdit->completer()->currentCompletion();
                row++;
            }
            ui->hallleft->hide();
            ui->undoView_3->hide();
            if(ui->searchEdit->text()=="")
                dic.clear();
            Search_results *result = new Search_results(dic,this);
            result->move(20,20);
            result->show();
            //回归主页
            connect(ui->Home,&QPushButton::clicked,[=]()
                    {
                        ui->hallleft->show();
                        ui->undoView_3->show();
                        result->hide();
                    });

        }
    }
    return QWidget::eventFilter(obj,event);
}

void GameHall::processFinished(int, QProcess::ExitStatus)
{
    this->show();
}

void GameHall::showContextMenu(const QPoint& pos)
{
    int i;
    for (i = 0; i < GameName.length(); ++i) {if(sender()->objectName()==GameName[i])break;}
    QMenu *menu = new QMenu(this);
    QDir dir(path+GameFile[i]);
    if(dir.exists())
    {
        QAction *action = new QAction("卸载游戏");
        menu->addAction(action);
        connect(action,&QAction::triggered,[&]()
                {
            dir.removeRecursively();
            removeY *remove = new removeY();
            remove->show();       
        });

    }
    else
    {

        QAction *action = new QAction("下载游戏");
        menu->addAction(action);
        connect(action,&QAction::triggered,[=]()
                {
            Download *download = new Download();
            DownloadTool *dt;
            dt = new DownloadTool(exe_path[i], path + GameFile[i]);
            connect(dt,SIGNAL(sigProgress(qint64, qint64, qreal)),download,SLOT(sltProgress(qint64, qint64, qreal)));
            connect(dt,SIGNAL(sigDownloadFinished()),download,SLOT(sltDownloadFinished()));
            download->show();
            dt->startDownload();
                });
    }
    HallBtn *sendor = (HallBtn*)sender();
    menu->exec(sendor->mapToGlobal(pos));
}
