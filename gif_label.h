#ifndef GIF_LABEL_H
#define GIF_LABEL_H

#include <QWidget>
#include <QLabel>
class Gif_Label : public QLabel
{
    Q_OBJECT
public:
    explicit Gif_Label(QWidget *parent = nullptr);

private:
    void enterEvent(QEnterEvent *e);
    void leaveEvent(QEvent *e);

signals:
    void leave();
    void enter();
};

#endif // GIF_LABEL_H
