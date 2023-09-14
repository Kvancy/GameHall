#include "hallbtn.h"
#include <QPropertyAnimation>
HallBtn::HallBtn(QWidget *parent)
    : QToolButton{parent}
{
    //设置鼠标样式(可点击)
    setCursor(Qt::PointingHandCursor);

    aml1->setDuration(200);
    aml1->setEasingCurve(QEasingCurve::Linear);
    aml2->setDuration(200);
    aml2->setEasingCurve(QEasingCurve::Linear);
    //建立菜单策略
    this->setContextMenuPolicy(Qt::CustomContextMenu);

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
    aml1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    aml1->setEndValue(QRect(this->x(),this->y()-5,this->width(),this->height()));
    aml1->start();
}

void HallBtn::btn_down()
{
    aml2->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    aml2->setEndValue(QRect(this->x(),this->y()+5,this->width(),this->height()));
    aml2->start();
}
