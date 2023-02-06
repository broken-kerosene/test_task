#ifndef RECIVEUDP_H
#define RECIVEUDP_H

#include <QObject>
#include <QUdpSocket>

class reciveUDP : public QObject
{
     Q_OBJECT

private:
     QUdpSocket* socket;

public:
     reciveUDP(QObject *parent = 0);
     void reciveDatagrams();

public slots:

};



#endif // RECIVEUDP_H
