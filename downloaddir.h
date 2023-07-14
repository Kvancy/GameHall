#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QEventLoop>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QRegExp>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void downloadFile(QUrl url,QString download_path);
    void downloadDir(QUrl path,QDir download_directory);
    void downloadDir(QUrl path,QString download_path);
private:
    QNetworkAccessManager manager;

};
#endif // WIDGET_H
