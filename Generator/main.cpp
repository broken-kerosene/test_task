#include <QCoreApplication>
#include <QString>
#include <QTime>
#include "matrix.h"
#include "sendudp.h"

void delay(int delMs)
{
    QTime dieTime= QTime::currentTime().addMSecs(delMs);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int n, m;
    bool ok;
    n = QString::fromLocal8Bit(*(argv+1)).toInt(&ok);
    m = QString::fromLocal8Bit(*(argv+2)).toInt(&ok);

    SendUDP server;
    QVector<QVector<int> > tmpmatrix;
    ulong id = 0;
    while(1){
        matrix tmp_arr(n, m);
        tmpmatrix = tmp_arr.getMatrix();
        server.makeMessage(id, m, n, tmpmatrix);
        server.sendMessage();
        qDebug() << "Message id: " << id;
        delay(500);
        id++;
    }
    return a.exec();
}
