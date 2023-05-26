#ifndef ROUNDIMG_H
#define ROUNDIMG_H
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
QPixmap PixmapToRound(const QPixmap &src, int radius)
{
    if (src.isNull())
    {
        return QPixmap();
    }

    //按比例缩放
    QPixmap pixmapa;
    if(src.width() != radius || src.height() != radius)
    {
        pixmapa = src.scaled(radius, radius, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
    else
    {
        pixmapa = src;
    }

    QPixmap pixmap(radius,radius);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QPainterPath path;
    path.addEllipse(0, 0, radius, radius);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, radius, radius, pixmapa);

    return pixmap;
}
#endif // ROUNDIMG_H
