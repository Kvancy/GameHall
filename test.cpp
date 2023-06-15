#include "test.h"
#include "ui_test.h"

Test::Test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test)
{
    ui->setupUi(this);
    ui->comboBox->setStyleSheet("QComboBox::down-arrow{image:url(qrc:/res/exclamation.png);}");
}

Test::~Test()
{
    delete ui;
}
