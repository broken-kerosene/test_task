#include "sendudp.h"


SendUDP::SendUDP(QObject *parent) :
    QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(6112);
}

void SendUDP::sendMessage()
{
    socket->writeDatagram(msg_, QHostAddress::LocalHost, 6112);
}

void SendUDP::makeMessage(int id, int m, int n, QVector<QVector<int> > matrix)
{
    QDataStream out( &msg_, QIODevice::WriteOnly );
    out << id << QDateTime::currentDateTime() << m << n << matrix;
}

void SendUDP::reciveDatagrams()
{
    QByteArray buffer;
    QHostAddress sender;
    quint16 senderPort;

    while(socket->hasPendingDatagrams()) {
        buffer.resize(socket->pendingDatagramSize());
        socket->readDatagram(buffer.data(), buffer.size(),
                           &sender, &senderPort);
    }
}

ulong SendUDP::getMessageSize() const
{
    //in bits
    return msg_.size()*8;
}
