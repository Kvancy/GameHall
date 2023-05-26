#ifndef SIGNSUCESS_H
#define SIGNSUCESS_H

#include <QDialog>
namespace Ui {
class SignSucess;
}

class SignSucess : public QDialog
{
    Q_OBJECT

public:
    explicit SignSucess(QDialog *parent = nullptr);
    ~SignSucess();

private:
    Ui::SignSucess *ui;
    void init();

signals:
    void Close();
};

#endif // SIGNSUCESS_H
