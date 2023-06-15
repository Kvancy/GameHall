#ifndef HALLBTN_H
#define HALLBTN_H

#include <QToolButton>
#include <QWidget>

class HallBtn : public QToolButton
{
    Q_OBJECT
public:
    explicit HallBtn(QWidget *parent = nullptr);

private:
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);
    void btn_up();
    void btn_down();
    bool flag=0;//记录目前按钮状态，弹起还是落下

signals:

};

#endif // HALLBTN_H
