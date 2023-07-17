#ifndef GAMEHALL_H
#define GAMEHALL_H

#include "gif_label.h"
#include "qdir.h"
#include "qnetworkaccessmanager.h"
#include <QWidget>
#include <QApplication>
#include <QProcess>
namespace Ui {
class GameHall;
}

class GameHall : public QWidget
{
    Q_OBJECT

public:
//    explicit GameHall(QWidget *parent = nullptr);
    GameHall(QString id,QWidget *parent = nullptr);
    ~GameHall();
    QString path=QApplication::applicationDirPath();
    QString ID;
    QNetworkReply *reply;
    QFile *file;

signals:


private slots:
    void slots_scroolwidget(int);
    void avatarUpload();
    void processFinished(int, QProcess::ExitStatus);
    void showContextMenu1(const QPoint& pos);
    void showContextMenu2(const QPoint& pos);
    void showContextMenu3(const QPoint& pos);
    void showContextMenu4(const QPoint& pos);
    void showContextMenu5(const QPoint& pos);

private:
    Ui::GameHall *ui;
    QString path_gif[3]={":/res/chuanqi.gif",":/res/lol.gif",":/res/1.gif"};//gif存储路径
    int index=0;//播放gif的索引
    void btncon(QMovie *movie,Gif_Label *gif);
    void search();
    void wheelEvent(QWheelEvent *event);
    void init();
    bool eventFilter(QObject *obj, QEvent *event);
    QNetworkAccessManager *manager;

};

#endif // GAMEHALL_H
