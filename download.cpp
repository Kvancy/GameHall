#include "download.h"
#include "ui_download.h"
#include <downloadtool.h>
Download::Download(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Download)
{
    ui->setupUi(this);
    setWindowTitle("下载游戏吧");
    connect(ui->stop,&QPushButton::clicked,[=](){
        this->hide();
    });
    setWindowIcon(QIcon(":/res/R-C.png"));
    ui->stop->setEnabled(false);
    ui->stop->setStyleSheet("QPushButton{background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0,"
                              "stop:0.0112994 rgba(64, 145, 252, 255),stop:1 rgba(255, 255, 255, 255));"
                              "color: rgb(255, 255, 255);"
                              "border:0px groove gray;border-radius:7px;padding:2px 4px;"
                              "font: 10pt 'Candara';}"
                              "QPushButton:hover{background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0,"
                              "stop:0.0112994 rgba(66, 175, 255, 255),stop:1 rgba(255, 255, 255, 255))};");
    ui->stop->setCursor(Qt::PointingHandCursor);
}

Download::~Download()
{
    delete ui;
}

void Download::sltProgress(qint64 bytesRead, qint64 totalBytes, qreal progress)
{
    ui->progressBar->setValue(progress*100);
    ui->progressBar->setFormat(QString::number(progress*100, 'f', 2) + "%");
}
void Download::sltDownloadFinished()
{
    ui->stop->setText(tr("下载完成"));
    ui->stop->setEnabled(true);

}
