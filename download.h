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

private:
    Ui::Download *ui;
};

#endif // DOWNLOAD_H
