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
    setWindowIcon(QIcon(":/res/R-C.png"));
    setWindowTitle("卸载成功！");
}

removeY::~removeY()
{
    delete ui;
}
