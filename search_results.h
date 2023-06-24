#ifndef SEARCH_RESULTS_H
#define SEARCH_RESULTS_H

#include "qapplication.h"
#include <QWidget>

namespace Ui {
class Search_results;
}

class Search_results : public QWidget
{
    Q_OBJECT

public:
    Search_results(QStringList dic,QWidget *parent = nullptr);
    ~Search_results();

private:
    Ui::Search_results *ui;
    QString globalpath = QApplication::applicationDirPath();

};

#endif // SEARCH_RESULTS_H
