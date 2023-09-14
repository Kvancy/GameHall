#include "m_thread.h"
#include "signsucess.h"

thread1::thread1(QObject *parent)
    : QObject{parent},QRunnable()
{
    setAutoDelete(1);
}

void thread1::run()
{
    Wating1 *wt = new Wating1(mainW);
    wt->show();
}
