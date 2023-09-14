#ifndef SIGNSUCESS_H
#define SIGNSUCESS_H
#include "qlabel.h"
#include "qmovie.h"
#pragma once
#include "qapplication.h"
#include <QDialog>
//小界面的类
class Wating1 : public QLabel
{
    Q_OBJECT

public:
    explicit Wating1(QWidget *parent = nullptr);
    ~Wating1();
    QMovie *m_move;

signals:

private:


};

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void mainwindow_show();

private:
    Ui::LoginWindow *ui;
    void mybtn();
    void sign();
    bool signcheck();
    void sign_init();
    void send();
    int verificationcode;

private slots:
    void Close();


};
namespace Ui {
class Download;
}

class Download : public QDialog
{
    Q_OBJECT

public:
    explicit Download(QWidget *parent = nullptr);
    ~Download();
private slots:
    void sltProgress(qint64 bytesRead, qint64 totalBytes, qreal progress);
    void sltDownloadFinished();

private:
    Ui::Download *ui;
};

namespace Ui {
class SignSucess;
}

class SignSucess : public QDialog
{
    Q_OBJECT

public:
    explicit SignSucess(QDialog *parent = nullptr);
    ~SignSucess();

private:
    Ui::SignSucess *ui;
    void init();

signals:
    void Close();
};

namespace Ui {
class Search_results;
}

class Search_results : public QWidget
{
    Q_OBJECT

public:
    Search_results(QStringList dic,QWidget *parent = nullptr);
    ~Search_results();

private:
    Ui::Search_results *ui;
    QString globalpath = QApplication::applicationDirPath();

};

namespace Ui {
class removeY;
}

class removeY : public QDialog
{
    Q_OBJECT

public:
    explicit removeY(QWidget *parent = nullptr);
    ~removeY();

private:
    Ui::removeY *ui;
};
#endif // SIGNSUCESS_H
