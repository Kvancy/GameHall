#include "download.h"
#include "ui_download.h"

Download::Download(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Download)
{
    ui->setupUi(this);

}

Download::~Download()
{
    delete ui;
}
