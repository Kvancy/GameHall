#include "removey.h"
#include "ui_removey.h"

removeY::removeY(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::removeY)
{
    ui->setupUi(this);
    connect(ui->OK,&QPushButton::clicked,[=]()
{
        this->hide();
    });
}

removeY::~removeY()
{
    delete ui;
}
