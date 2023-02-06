#include "reciveudp.h"

reciveUDP::reciveUDP(QObject *parent) :
    QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 6112);
    //connect(socket, SIGNAL(readyRead()), this, SLOT(reciveDatagrams));
}

void reciveUDP::reciveDatagrams()
{
  QByteArray buffer;
  QHostAddress sender;
  quint16 senderPort;

  do {
      buffer.resize(socket->pendingDatagramSize());
      socket->readDatagram(buffer.data(), buffer.size(),
                           &sender, &senderPort);
      qDebug() << "Message from: " << sender.toString();
      qDebug() << "Message port: " << senderPort;
      qDebug() << "Message: " << buffer;

  } while(socket->hasPendingDatagrams());

}
