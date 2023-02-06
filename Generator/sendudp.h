#ifndef SENDUDP_H
#define SENDUDP_H

#include <QObject>
#include <QUdpSocket>
#include <QDateTime>
#include <QDataStream>

class SendUDP : public QObject
{
    Q_OBJECT
public:
    explicit SendUDP(QObject *parent = 0);
    void makeMessage(int id, int m, int n, QVector<QVector<int> > matrix);
    void sendMessage();
    ulong getMessageSize() const;
signals:

public slots:
    void reciveDatagrams();

private:
    QUdpSocket *socket;
    QByteArray msg_;

};

#endif // SENDUDP_H
