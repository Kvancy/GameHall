#include "gamehall.h"
#include "ui_gamehall.h"
#include <QProcess>
#include <QMovie>
#include "gif_label.h"
#include <QCompleter>
#include <QWheelEvent>
#include <QBuffer>
#include <QFileDialog>
#include "roundimg.h"
#include <QSqlQuery>
GameHall::GameHall(QString id,QWidget *parent) ://id记录登录用户的用户id
    QWidget(parent),
    ui(new Ui::GameHall)
{
    ui->setupUi(this);
    setWindowTitle("Game Hall!");
    setMouseTracking(true);
    ID = id;
    //设置gif播放
    QMovie *movie = new QMovie;
    movie->setParent(this);
    movie->setFileName(path_gif[index]);
    movie->setScaledSize(QSize(ui->gif->width(),(ui->gif->height())));
    ui->gif->setMovie(movie);
    movie->start();

    setMouseTracking(true);
    init();
    btncon(movie,ui->gif);
    search();


}

GameHall::~GameHall()
{
    delete ui;
}

void GameHall::init()
{
    ui->left->hide();
    ui->right->hide();
    //加载左右移图片
    ui->left->setText("");
    ui->left->setIcon(QIcon(":/res/left.png"));
    ui->left->setIconSize(QSize(85,85));
    ui->right->setText("");
    ui->right->setIcon(QIcon(":/res/right.png"));
    ui->right->setIconSize(QSize(85,85));
    ui->left->setStyleSheet("QPushButton{border-radius:35px;}"
                             "QPushButton:hover{background-color:rgb(255, 255, 255); }"
                             "QPushButton:pressed{background-color:rgb(204, 228, 247);}"
                             );

    ui->right->setStyleSheet("QPushButton{border-radius:35px;}"
                            "QPushButton:hover{background-color:rgb(255, 255, 255); }"
                            "QPushButton:pressed{background-color:rgb(204, 228, 247);}"
                            );
    //设置游戏图标的图像
    ui->fiveline->setIcon(QIcon(":/res/fiveline.png"));
    ui->fiveline->setIconSize(QSize(ui->fiveline->width()-10,ui->fiveline->height()-10));
    ui->fiveline->setStyleSheet("QToolButton{border-style: flat;}");

    ui->chat->setIcon(QIcon(":/res/guess.jpg"));
    ui->chat->setIconSize(QSize(ui->fiveline->width()-10,ui->fiveline->height()-10));
    ui->chat->setStyleSheet("QToolButton{border-style: flat;}");

    ui->zhuoqiu->setIcon(QIcon(":/res/Tabletennis.png"));
    ui->zhuoqiu->setIconSize(QSize(ui->fiveline->width()-10,ui->fiveline->height()-10));
    ui->zhuoqiu->setStyleSheet("QToolButton{border-style: flat;}");

    ui->hlddz->setIcon(QIcon(":/res/landlord.png"));
    ui->hlddz->setIconSize(QSize(ui->fiveline->width()-10,ui->fiveline->height()-10));
    ui->hlddz->setStyleSheet("QToolButton{border-style: flat;}");

    ui->ayqj->setIcon(QIcon(":/res/ayqj.png"));
    ui->ayqj->setIconSize(QSize(ui->fiveline->width()-10,ui->fiveline->height()-10));
    ui->ayqj->setStyleSheet("QToolButton{border-style: flat;}");

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

void GameHall::btncon(QMovie *movie,Gif_Label *gif)
{
    connect(ui->fiveline,&QPushButton::clicked,[=]()
            {
                QProcess process(this);
                process.startDetached(path+"/games/five2line/five2line.exe");
            });
    connect(ui->chat,&QPushButton::clicked,[=]()
            {
                QProcess process(this);
                process.startDetached(path+"/games/onlineChat/chat.exe");
            });
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
    //鼠标进入退出按钮出现或隐藏
    connect(gif,&Gif_Label::leave,[=]()
            {
        ui->left->hide();
        ui->right->hide();
            });
    connect(gif,&Gif_Label::enter,[=]()
            {
                ui->left->show();
                ui->right->show();
            });
    //移动滚动条效果
    connect(ui->verticalScrollBar,SIGNAL(valueChanged(int)),this,SLOT(slots_scroolwidget(int)));
    connect(ui->test,&QPushButton::clicked,this,&GameHall::avatarUpload);
}

void GameHall::search()
{
    QStringList dic;
    //数据库暂时崩了，回来优化
    dic << "first" << "second" << "firsts" << "seconds";
    QCompleter *completer = new QCompleter(dic,this);
    completer->setFilterMode(Qt::MatchContains);
    ui->searchEdit->setCompleter(completer);


}

void GameHall::slots_scroolwidget(int value)
{
    double p=static_cast<double>(value)/static_cast<double>(ui->verticalScrollBar->maximum());
    //30是wiget横坐标，800是wigit的底y坐标-窗口的高度，+30是为了防止窗口y坐标到全局0
    ui->hall->move(30,-(ui->hall->height()-800)*p+30);


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

void GameHall::avatarUpload()
{
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("open image file"),
        "./", tr("Image files(*.png *.jpg)"));
    //设置缓冲区保存二进制
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
    qDebug()<<format;
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

















