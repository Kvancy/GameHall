#ifndef RANKLBABEL_H
#define RANKLBABEL_H

#include <QLabel>
#include <QApplication>
class rankLbabel : public QLabel
{
    Q_OBJECT
public:
    explicit rankLbabel(QWidget *parent = nullptr);
    void mouseDoubleClickEvent(QMouseEvent *e);
    QString path=QApplication::applicationDirPath();
private:
    void leaveEvent(QEvent *event);
    void enterEvent(QEnterEvent *event);

signals:

};

#endif // RANKLBABEL_H
