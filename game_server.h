#ifndef GAME_SERVER_H
#define GAME_SERVER_H
#include <QTcpServer>
#include <QList>
#include <QSharedPointer>

#include "game_lobby.h"

class Game_server : public QTcpServer
{
    Q_OBJECT
    void send_data_positoin_to_client(const qint32 id, const qint8, const qint8);
    void send_lobbies_list();

protected:
    QTcpSocket *socket;
    QList<QSharedPointer<QTcpSocket>> sockets;
    QList<Game_lobby*> lobbies;
    QByteArray data;

public:
    Game_server();
public slots:
    void incomingConnection(qintptr handle) override;
    void read_request();
};

#endif // GAME_SERVER_H
