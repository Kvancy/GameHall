//工具类
#ifndef ROUNDIMG_H
#define ROUNDIMG_H
#pragma once
#include "qtcpsocket.h"
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QObject>        // QObject类是Qt对象模型的核心
#include <QUrl>           // QUrl类提供了使用URL的便捷接口
#include <QFile>          // QFile类用于对文件进行读写操作
#include <QDir>           // QDir类用于操作路径名及底层文件系统
#include <QPointer>       // QPointer指针引用的对象被销毁时候,会自动指向NULL,解决指针悬挂问题
#include <QApplication>   // 此处用于获取当前程序绝对路径
#include <QNetworkReply>  // QNetworkReply类封装了使用QNetworkAccessManager发布的请求相关的回复信息。
#include <QNetworkAccessManager>  // QNetworkAccessManager类为应用提供发送网络请求和接收答复的API接口
#include <memory>         // 使用std::unique_ptr需要包含该头文件
//下载网络文件的一个工具类
class DownloadTool : public QObject  // 继承QObject
{
    Q_OBJECT              // 加入此宏，才能使用QT中的signal和slot机制

public:
    // 构造函数参数:  1)http文件完整的url  2)保存的路径
    explicit DownloadTool(const QString& downloadUrl, const QString& savePath, QObject* parent = nullptr);
    ~DownloadTool();

    void startDownload();  // 开始下载文件
    void cancelDownload(); // 取消下载文件

Q_SIGNALS:
    void sigProgress(qint64 bytesRead, qint64 totalBytes, qreal progress);  // 下载进度信号
    void sigDownloadFinished();  // 下载完成信号

private Q_SLOTS:
    void httpFinished();    // QNetworkReply::finished对应的槽函数
    void httpReadyRead();   // QIODevice::readyRead对应的槽函数

    void networkReplyProgress(qint64 bytesRead, qint64 totalBytes);  // QNetworkReply::downloadProgress对应的槽函数

private:
    void startRequest(const QUrl& requestedUrl);
    std::unique_ptr<QFile> openFileForWrite(const QString& fileName);

private:
    QString m_downloadUrl;  // 保存构造时传入的下载url
    QString m_savePath;     // 保存构造时传入的保存路径

    const QString defaultFileName = "tmp";  // 默认下载到tmp文件夹

    QUrl url;
    QNetworkAccessManager qnam;
    QPointer<QNetworkReply> reply;
    std::unique_ptr<QFile> file;
    bool httpRequestAborted;
};
class Smtp
{
public:
    Smtp(QByteArray username,QByteArray password);
    ~Smtp();
    void send(QByteArray recvaddr,QString subject,QString content);
private:
    QTcpSocket * clientsocket;
    QByteArray username;
    QByteArray password;
    QByteArray recvaddr;
    QByteArray mailfrom = "mail from:<";
    QByteArray rcptto = "rcpt to:<";
    QByteArray prefrom = "from:";
    QByteArray preto = "to:";
    QByteArray presubject ="subject:";
    QString subject;                //主题
    QString content;                //发送内容
    QByteArray recvdata;            //接收到的数据
};
QPixmap PixmapToRound(const QPixmap &src, int radius);


#endif // ROUNDIMG_H
