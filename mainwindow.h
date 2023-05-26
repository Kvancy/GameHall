#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QApplication>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void login_init();
    void mybtn();
    void login_judge();
    void signDown();
    void linkDatabase();
    int check();
    void pwdRemember();
    bool ischecked;
    QString inipath= QCoreApplication::applicationDirPath() + "/init.ini";
    QSqlDatabase database;

private slots:
    void checkbox_checked();
};
#endif // MAINWINDOW_H
