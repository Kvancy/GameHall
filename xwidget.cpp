#include "xwidget.h"
#include "ui_xwidget.h"
#include <QMouseEvent>
XWidget::XWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);    //隐藏标题栏（无边框）
    setAttribute(Qt::WA_StyledBackground);      //启用样式背景绘制
    setAttribute(Qt::WA_TranslucentBackground); //背景透明
    setAttribute(Qt::WA_Hover);//为了实现鼠标的位置信息获取不受子控件的影响，启动鼠标悬浮追踪


}

XWidget::~XWidget()
{
    delete ui;
}

bool XWidget::event(QEvent *event)
{
    if (event->type() == QEvent::HoverMove) {
        QHoverEvent *hoverEvent = static_cast<QHoverEvent *>(event);
        QMouseEvent mouseEvent(QEvent::MouseMove, hoverEvent->pos(),
                               Qt::NoButton, Qt::NoButton, Qt::NoModifier);
        mouseMoveEvent(&mouseEvent);
    }

    return QWidget::event(event);
}

void XWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_bIsPressed = true;
        m_pressPoint = event->globalPos();
    }

    return QWidget::mousePressEvent(event);
}

void XWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bIsPressed) {
        if (m_bIsResizing) {
            m_movePoint = event->globalPos() - m_pressPoint;
            m_pressPoint += m_movePoint;
        } else {
            if (!m_bIsDoublePressed && windowState() == Qt::WindowMaximized) {
                restoreWidget();
                QPointF point(width() * ((double)(event->globalPos().x())/QApplication::desktop()->width()),
                              height() * ((double)(event->globalPos().y())/QApplication::desktop()->height()));

                move(event->globalPos() - point.toPoint());

                m_pressPoint = event->globalPos();
            }

            QPoint point = event->globalPos() - m_pressPoint;
            move(pos() + point);

            m_pressPoint = event->globalPos();
        }
    }

    if (windowState() != Qt::WindowMaximized) {
        updateRegion(event);
    }

    QWidget::mouseMoveEvent(event);
}

void XWidget::updateRegion(QMouseEvent *event)
{
    QRect mainRect = geometry();

    int marginTop = event->globalY() - mainRect.y();
    int marginBottom = mainRect.y() + mainRect.height() - event->globalY();
    int marginLeft = event->globalX() - mainRect.x();
    int marginRight = mainRect.x() + mainRect.width() - event->globalX();

    if (!m_bIsResizing) {
        if ( (marginRight >= MARGIN_MIN_SIZE && marginRight <= MARGIN_MAX_SIZE)
            && ((marginBottom <= MARGIN_MAX_SIZE) && marginBottom >= MARGIN_MIN_SIZE) ) {
            m_direction = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);
        } else if ( (marginTop >= MARGIN_MIN_SIZE && marginTop <= MARGIN_MAX_SIZE)
                   && (marginRight >= MARGIN_MIN_SIZE && marginRight <= MARGIN_MAX_SIZE)) {
            m_direction = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);
        } else if ( (marginLeft >= MARGIN_MIN_SIZE && marginLeft <= MARGIN_MAX_SIZE)
                   && (marginTop >= MARGIN_MIN_SIZE && marginTop <= MARGIN_MAX_SIZE) ) {
            m_direction = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);
        } else if ( (marginLeft >= MARGIN_MIN_SIZE && marginLeft <= MARGIN_MAX_SIZE)
                   && (marginBottom >= MARGIN_MIN_SIZE && marginBottom <= MARGIN_MAX_SIZE)) {
            m_direction = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);
        } else if (marginBottom <= MARGIN_MAX_SIZE && marginBottom >= MARGIN_MIN_SIZE) {
            m_direction = DOWN;
            setCursor(Qt::SizeVerCursor);
        } else if (marginLeft <= MARGIN_MAX_SIZE - 1 && marginLeft >= MARGIN_MIN_SIZE - 1) {
            m_direction = LEFT;
            setCursor(Qt::SizeHorCursor);
        } else if (marginRight <= MARGIN_MAX_SIZE && marginRight >= MARGIN_MIN_SIZE) {
            m_direction = RIGHT;
            setCursor(Qt::SizeHorCursor);
        } else if (marginTop <= MARGIN_MAX_SIZE && marginTop >= MARGIN_MIN_SIZE) {
            m_direction = UP;
            setCursor(Qt::SizeVerCursor);
        } else {
            if (!m_bIsPressed) {
                setCursor(Qt::ArrowCursor);
            }
        }
    }

    if (NONE != m_direction) {
        m_bIsResizing = true;
        resizeRegion(marginTop, marginBottom, marginLeft, marginRight);
    }
}

void XWidget::resizeRegion(int marginTop, int marginBottom,
                           int marginLeft, int marginRight)
{
    if (m_bIsPressed) {
        switch (m_direction) {
        case BOTTOMRIGHT:
        {
            QRect rect = geometry();
            rect.setBottomRight(rect.bottomRight() + m_movePoint);
            setGeometry(rect);
        }
        break;
        case TOPRIGHT:
        {
            if (marginLeft > minimumWidth() && marginBottom > minimumHeight()) {
                QRect rect = geometry();
                rect.setTopRight(rect.topRight() + m_movePoint);
                setGeometry(rect);
            }
        }
        break;
        case TOPLEFT:
        {
            if (marginRight > minimumWidth() && marginBottom > minimumHeight()) {
                QRect rect = geometry();
                rect.setTopLeft(rect.topLeft() + m_movePoint);
                setGeometry(rect);
            }
        }
        break;
        case BOTTOMLEFT:
        {
            if (marginRight > minimumWidth() && marginTop> minimumHeight()) {
                QRect rect = geometry();
                rect.setBottomLeft(rect.bottomLeft() + m_movePoint);
                setGeometry(rect);
            }
        }
        break;
        case RIGHT:
        {
            QRect rect = geometry();
            rect.setWidth(rect.width() + m_movePoint.x());
            setGeometry(rect);
        }
        break;
        case DOWN:
        {
            QRect rect = geometry();
            rect.setHeight(rect.height() + m_movePoint.y());
            setGeometry(rect);
        }
        break;
        case LEFT:
        {
            if (marginRight > minimumWidth()) {
                QRect rect = geometry();
                rect.setLeft(rect.x() + m_movePoint.x());
                setGeometry(rect);
            }
        }
        break;
        case UP:
        {
            if (marginBottom > minimumHeight()) {
                QRect rect = geometry();
                rect.setTop(rect.y() + m_movePoint.y());
                setGeometry(rect);
            }
        }
        break;
        default:
        {
        }
        break;
        }
    } else {
        m_bIsResizing = false;
        m_direction = NONE;
    }
}

void XWidget::leaveEvent(QEvent *event)
{
    m_bIsPressed = false;
    m_bIsDoublePressed = false;
    m_bIsResizing = false;

    QWidget::leaveEvent(event);
}

void XWidget::createShadow()
{
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setColor(Qt::black);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setBlurRadius(13);
    ui->widgetContent->setGraphicsEffect(shadowEffect);
}

void XWidget::maximizeWidget()
{
    ui->pushButtonRestore->show();
    ui->pushButtonMax->hide();

    ui->verticalLayoutShadow->setContentsMargins(0, 0, 0, 0);

    showMaximized();
}

void XWidget::restoreWidget()
{
    ui->pushButtonRestore->hide();
    ui->pushButtonMax->show();

    ui->verticalLayoutShadow->setContentsMargins(9, 9, 9, 9);

    showNormal();
}
