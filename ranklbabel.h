#ifndef RANKLBABEL_H
#define RANKLBABEL_H

#include <QLabel>
#include <QApplication>
#include <QProcess>
class rankLbabel : public QLabel
{
    Q_OBJECT
public:
    explicit rankLbabel(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *e);
    QString path=QApplication::applicationDirPath();
private:
    void leaveEvent(QEvent *event);
    void enterEvent(QEnterEvent *event);

private slots:
    void processFinished(int, QProcess::ExitStatus);

signals:
    void Tohide();
    void Toshow();

};

#endif // RANKLBABEL_H
