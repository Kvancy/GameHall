#include "ranklbabel.h"
#include <QDebug>
#include <QMouseEvent>
#include <QProcess>
rankLbabel::rankLbabel(QWidget *parent)
    : QLabel{parent}
{
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("font: 12pt '幼圆';"
                  "padding-left:5px;"
                 "border-radius:20px;"
                  "background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0,"
                              "stop:0.0112994 rgba(64, 145, 252, 255),stop:1 rgba(255, 255, 255, 255));"
                              "color: rgb(255, 255, 255)");
    setFrameShape(NoFrame);

}

void rankLbabel::mousePressEvent(QMouseEvent *e)
{
    //起始纵坐标为240，间隔20，高度40
    if(e->globalY()<(240+20*0+40)&&e->globalY()>(240+20*0))
    {
        QProcess process(this);
        process.startDetached(path+"/games/five2line/five2line.exe");
    }
}

void rankLbabel::leaveEvent(QEvent *event)
{
    setStyleSheet("font: 12pt '幼圆';"
                  "padding-left:5px;"
                  "border-radius:20px;"
                  "background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0,"
                  "stop:0.0112994 rgba(64, 145, 252, 255),stop:1 rgba(255, 255, 255, 255));"
                  "color: rgb(255, 255, 255)");
}
void rankLbabel::enterEvent(QEnterEvent *event)
{
    setStyleSheet(
        "font: 12pt '幼圆';"
        "border-radius:20px;"
        "padding-left:5px;"
        "border-color:rgb(255,0,0);"
        "background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0,"
        "stop:0.0112994 rgba(66, 175, 255, 255),stop:1 rgba(255, 255, 255, 255))};");
}

