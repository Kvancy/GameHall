#include "hallbtn.h"
#include <QPropertyAnimation>
HallBtn::HallBtn(QWidget *parent)
    : QToolButton{parent}
{
    //设置鼠标样式(可点击)
    setCursor(Qt::PointingHandCursor);
}


void HallBtn::leaveEvent(QEvent *event)
{
    btn_down();
}

void HallBtn::enterEvent(QEnterEvent *event)
{
    btn_up();
}

void HallBtn::btn_up()
{
    QPropertyAnimation *aml = new QPropertyAnimation(this,"geometry");
    aml->setDuration(100);
    aml->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    aml->setEndValue(QRect(this->x(),this->y()-5,this->width(),this->height()));
    aml->setEasingCurve(QEasingCurve::OutBounce);
    aml->start();

}

void HallBtn::btn_down()
{
    QPropertyAnimation *aml = new QPropertyAnimation(this,"geometry");
    aml->setDuration(200);
    aml->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    aml->setEndValue(QRect(this->x(),this->y()+5,this->width(),this->height()));
    aml->setEasingCurve(QEasingCurve::OutBounce);
    aml->start();

}
