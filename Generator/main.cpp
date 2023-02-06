#include <QCoreApplication>
#include <QString>
#include <QElapsedTimer>
#include <QDebug>
#include "matrix.h"
#include "sendudp.h"


const int MBIT = 10e6;
const int NANO = 1e9;

void wait(int nsecs)
{
    QElapsedTimer timer;
    timer.start();
    while(timer.nsecsElapsed() < nsecs)
        QCoreApplication::processEvents();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int n, m;
    bool ok;
    n = QString::fromLocal8Bit(*(argv+1)).toInt(&ok);
    m = QString::fromLocal8Bit(*(argv+2)).toInt(&ok);

    SendUDP server;
    server.n = n;
    server.m = m;
    server.matrix = matrix(n, m).getMatrix();
    server.makeMessage();
    server.delay_ = double(server.getMessageSize())/double(MBIT) * NANO; //nsecs
    //server.startTransmission();
    while(1){
        server.sendMessage();
        wait(int(server.delay_));
    }
    return a.exec();
}
