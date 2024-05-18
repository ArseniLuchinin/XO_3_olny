#ifndef GAME_SERVER_H
#define GAME_SERVER_H
#include <QTcpServer>
#include <QList>
#include <QSharedPointer>

#include "game_lobby.h"

class Game_server : public QTcpServer
{
    Q_OBJECT
protected:
    QTcpSocket *socket;
    QList<QSharedPointer<QTcpSocket>> sockets;
    QByteArray data;

public:
    Game_server();

public slots:
    void incomingConnection(qintptr handle) override;
    void read_request();
};

#endif // GAME_SERVER_H
