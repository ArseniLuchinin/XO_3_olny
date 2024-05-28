#ifndef GAME_SERVER_H
#define GAME_SERVER_H
#include <QTcpServer>
#include <QList>
#include <QSharedPointer>

#include "game_lobby.h"

#define SEND_ERROR_COD 0
#define SEND_POS_COD 1
#define SEND_LOBBIES_COD 2
#define SEND_LOBBY_SET_COD 3
#define MOVE_COD 4


class Game_server : public QTcpServer
{
    Q_OBJECT
    void send_data_positoin_to_client(const qint32 id, const qint8, const qint8, QTcpSocket*);
    void send_lobbies_list(QTcpSocket*);
    void handle_reqests(const qint8 cod, QDataStream& in, QTcpSocket *sc);
    void send_error(QTcpSocket *sc);
    void send_figure_to_client(const QChar, QTcpSocket *sc);
    void send_move(const qint8);
protected:
    QTcpSocket *socket;
    QList<Game_lobby*> lobbies;
    QByteArray data;

public:
    Game_server();
public slots:
    void incomingConnection(qintptr handle) override;
    void read_request();
};

#endif // GAME_SERVER_H
