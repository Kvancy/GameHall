#ifndef M_THREAD_H
#define M_THREAD_H

#include "gamehall.h"
#include "mainwindow.h"
#include <QObject>
#include <QRunnable>
class thread1 : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit thread1(QObject *parent = nullptr);
    void run();
    void GetUsername(QString username)
    {
        this->username = username;
    }
    void Setmainw(MainWindow *mainw)
    {
        mainW = mainw;
    }
signals:
    void runout(GameHall* gamehall);
private:
    QString username;
    MainWindow *mainW;

};

#endif // M_THREAD_H
