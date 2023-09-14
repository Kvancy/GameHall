#ifndef GAMEHALL_H
#define GAMEHALL_H
#include "hallbtn.h"
#include "qdir.h"
#include "qlabel.h"
#pragma once
#include "qnetworkaccessmanager.h"
#include <QWidget>
#include <QApplication>
#include <QProcess>
namespace Ui {
class GameHall;
}

//游戏大厅界面的类
class GameHall : public QWidget
{
    Q_OBJECT

public:
//    explicit GameHall(QWidget *parent = nullptr);
    GameHall(QString id="",QWidget *parent = nullptr);
    ~GameHall();
    QString path=QApplication::applicationDirPath();
    QString ID;
    QNetworkReply *reply;
    QFile *file;
    QStringList GameFile;
    QStringList exe_path;
    QStringList DownPath;
    QStringList GameName;


signals:
    void m_show();


private slots:
    void slots_scroolwidget(int);
    void avatarUpload();
    void processFinished(int, QProcess::ExitStatus);
    void showContextMenu(const QPoint& pos);

private:
    Ui::GameHall *ui;
    QString path_gif[3]={":/res/chuanqi.gif",":/res/lol.gif",":/res/1.gif"};//gif存储路径
    int index=0;//播放gif的索引
    void btncon(QMovie *movie,QLabel *gif,HallBtn** btn);
    void search();
    void wheelEvent(QWheelEvent *event);
    void init();
    bool eventFilter(QObject *obj, QEvent *event);
    QNetworkAccessManager *manager;

};

#endif // GAMEHALL_H
