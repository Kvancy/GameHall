#ifndef HALLBTN_H
#define HALLBTN_H
#pragma once
#include "qpropertyanimation.h"
#include <QToolButton>
#include <QWidget>
//大厅启动游戏的按钮类,按钮类
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
    QPropertyAnimation *aml1 = new QPropertyAnimation(this);
    QPropertyAnimation *aml2 = new QPropertyAnimation(this);



signals:

};

#endif // HALLBTN_H
