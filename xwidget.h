#ifndef XWIDGET_H
#define XWIDGET_H

#include <QWidget>

namespace Ui {
class XWidget;
}

class XWidget : public QWidget
{
    Q_OBJECT

public:
    explicit XWidget(QWidget *parent = nullptr);
    ~XWidget();
    bool event(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void updateRegion(QMouseEvent *event);
    void resizeRegion(int marginTop, int marginBottom,int marginLeft, int marginRight);
    void leaveEvent(QEvent *event);
    void createShadow();
    void maximizeWidget();
    void restoreWidget();
    bool m_bIsPressed;
    QPoint m_pressPoint;
    bool m_bIsResizing;
    QPoint m_movePoint;
    bool m_bIsDoublePressed;


private:
    Ui::XWidget *ui;
};

#endif // XWIDGET_H
