#ifndef RECUDP_H
#define RECUDP_H

#include <QObject>



class RecUDP : public QObject
{
    Q_OBJECT
public:
    explicit RecUDP(QObject *parent = 0);
    void dataRecived();


//private slots:
//    void processPendingDatagrams();

private:
    QUdpSocket *socket;

};

#endif // RECUDP_H
