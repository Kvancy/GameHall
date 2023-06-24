#ifndef GAMEHALL_H
#define GAMEHALL_H

#include "gif_label.h"
#include <QWidget>
#include <QApplication>
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

signals:


private slots:
    void slots_scroolwidget(int);
    void avatarUpload();

private:
    Ui::GameHall *ui;
    QString path_gif[3]={":/res/chuanqi.gif",":/res/lol.gif",":/res/1.gif"};//gif存储路径
    int index=0;//播放gif的索引
    void btncon(QMovie *movie,Gif_Label *gif);
    void search();
    void wheelEvent(QWheelEvent *event);
    void init();
    bool eventFilter(QObject *obj, QEvent *event);

};

#endif // GAMEHALL_H
