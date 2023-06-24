#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();


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

#endif // LOGINWINDOW_H
