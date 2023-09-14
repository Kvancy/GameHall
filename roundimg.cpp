#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <roundimg.h>
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

Smtp::Smtp(QByteArray username,QByteArray password) //初始化发送者
{
    if(username.contains("@qq"))
    {
        this->username = username;
        this->password = password;
    }
    else
        qDebug()<<"NOT qq";
}
void Smtp::send(QByteArray recvaddr,QString subject,QString content) //发送邮件
{
    this->recvaddr = recvaddr;
    this->subject = subject;
    this->content = content;
    QByteArray usernametmp = this->username;
    QByteArray recvaddrtmp = this->recvaddr;
    clientsocket=new QTcpSocket();
    this->clientsocket->connectToHost("smtp.qq.com",25,QTcpSocket::ReadWrite);
    this->clientsocket->waitForConnected(1000);
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    this->clientsocket->write("HELO smtp.qq.com\r\n");
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    this->clientsocket->write("AUTH LOGIN\r\n");
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    this->clientsocket->write(username.toBase64().append("\r\n"));
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    this->clientsocket->write(password.toBase64().append("\r\n"));
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    this->clientsocket->write(mailfrom.append(usernametmp.append(">\r\n")));
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    this->clientsocket->write(rcptto.append(recvaddrtmp.append(">\r\n")));
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    this->clientsocket->write("data\r\n");
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();

    usernametmp = this->username;
    recvaddrtmp = this->recvaddr;
    this->clientsocket->write(prefrom.append(usernametmp.append("\r\n")));
    this->clientsocket->write(preto.append(recvaddrtmp.append("\r\n")));
    this->clientsocket->write(presubject.append(subject.toLocal8Bit().append("\r\n")));
    this->clientsocket->write("\r\n");
    this->clientsocket->write(content.toLocal8Bit().append("\r\n"));
    this->clientsocket->write(".\r\n");
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();

    this->clientsocket->write("quit\r\n");
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();

}
Smtp::~Smtp()
{
    delete this->clientsocket;
}


DownloadTool::DownloadTool(const QString& downloadUrl, const QString& savePath, QObject* parent)
    : QObject(parent)
{
    m_downloadUrl = downloadUrl;
    m_savePath    = savePath;
}

DownloadTool::~DownloadTool() {}

void DownloadTool::startDownload()
{
    const QUrl newUrl = QUrl::fromUserInput(m_downloadUrl);

    if (!newUrl.isValid()) {
        return;
    }

    QString fileName = newUrl.fileName();

    if (fileName.isEmpty()) fileName = defaultFileName;
    if (m_savePath.isEmpty()) { m_savePath = QApplication::applicationDirPath() + "/tmp"; }
    if (!QFileInfo(m_savePath).isDir()) {
        QDir dir;
        dir.mkpath(m_savePath);
    }

    fileName.prepend(m_savePath + '/');
    if (QFile::exists(fileName)) { QFile::remove(fileName); }
    file = openFileForWrite(fileName);
    if (!file) return;

    startRequest(newUrl);
}

void DownloadTool::cancelDownload()
{
    httpRequestAborted = true;
    reply->abort();
}

void DownloadTool::httpFinished()
{
    QFileInfo fi;
    if (file) {
        fi.setFile(file->fileName());
        file->close();
        file.reset();
    }

    if (httpRequestAborted) {
        return;
    }

    if (reply->error()) {
        QFile::remove(fi.absoluteFilePath());
        return;
    }

    const QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    if (!redirectionTarget.isNull()) {
        const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());
        file = openFileForWrite(fi.absoluteFilePath());
        if (!file) { return; }
        startRequest(redirectedUrl);
        return;
    }

    Q_EMIT sigDownloadFinished();
}

void DownloadTool::httpReadyRead()
{
    if (file) file->write(reply->readAll());
}

void DownloadTool::networkReplyProgress(qint64 bytesRead, qint64 totalBytes)
{
    qreal progress = qreal(bytesRead) / qreal(totalBytes);
    Q_EMIT sigProgress(bytesRead, totalBytes, progress);
}

void DownloadTool::startRequest(const QUrl& requestedUrl)
{
    url = requestedUrl;
    httpRequestAborted = false;

    reply = qnam.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &DownloadTool::httpFinished);
    connect(reply, &QIODevice::readyRead, this, &DownloadTool::httpReadyRead);
    connect(reply, &QNetworkReply::downloadProgress, this, &DownloadTool::networkReplyProgress);
}

std::unique_ptr<QFile> DownloadTool::openFileForWrite(const QString& fileName)
{
    std::unique_ptr<QFile> file(new QFile(fileName));
    if (!file->open(QIODevice::WriteOnly)) {
        return nullptr;
    }
    return file;
}

