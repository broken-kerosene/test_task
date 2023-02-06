#include "sendudp.h"

const int PORT = 6112;

SendUDP::SendUDP(QObject *parent) :
    QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(PORT);

    timer = new QTimer(this);
    delay_ = 1;
     //time specified in ms
    id_=0;
}
void SendUDP::sendMessage()
{
    makeMessage();
    socket->writeDatagram(msg_, QHostAddress::LocalHost, PORT);
    id_++;
}


void SendUDP::sendMessageSlot()
{
    makeMessage();
    socket->writeDatagram(msg_, QHostAddress::LocalHost, PORT);
    id_++;
}

void SendUDP::makeMessage()
{
    QDataStream out(&msg_, QIODevice::WriteOnly);
    out << id_ << QDateTime::currentDateTime() << m << n << matrix;
}

ulong SendUDP::getMessageSize() const
{
    return msg_.size()*8; //in bits
}

void SendUDP::startTransmission()
{
    timer->start(delay_);
    connect(timer, SIGNAL(timeout()), this, SLOT(sendMessageSlot()));
}



