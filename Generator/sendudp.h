#ifndef SENDUDP_H
#define SENDUDP_H

#include <QObject>
#include <QUdpSocket>
#include <QDateTime>
#include <QDataStream>
#include <QTimer>

class SendUDP : public QObject
{
    Q_OBJECT
public:
    explicit SendUDP(QObject *parent = 0);
    void startTransmission();
    void makeMessage();
    void sendMessage();
    ulong getMessageSize() const;


public slots:
    void sendMessageSlot();

private:
    QUdpSocket *socket;
    QTimer *timer;
    QByteArray msg_;
    quint32 id_;

 public:
    QVector<QVector<int> > matrix;
    int n, m;
    double delay_;

};

#endif // SENDUDP_H
