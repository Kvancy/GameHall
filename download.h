#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QDialog>

namespace Ui {
class Download;
}

class Download : public QDialog
{
    Q_OBJECT

public:
    explicit Download(QWidget *parent = nullptr);
    ~Download();
private slots:
    void sltProgress(qint64 bytesRead, qint64 totalBytes, qreal progress);
    void sltDownloadFinished();

private:
    Ui::Download *ui;
};

#endif // DOWNLOAD_H
