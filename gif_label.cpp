#include "gif_label.h"
#include <QMovie>
Gif_Label::Gif_Label(QWidget *parent)
    : QLabel{parent}
{
    setMouseTracking(true);
}

void Gif_Label::enterEvent(QEnterEvent *e)
{
    emit enter();
}

void Gif_Label::leaveEvent(QEvent *e)
{
    emit leave();
}
