#ifndef GAME_SERVER_H
#define GAME_SERVER_H
#include <QTcpServer>
#include <QList>
#include <QSharedPointer>

#include "game_lobby.h"

#define ERROR_COD 0
#define POSITION_COD 1
#define LOBBIES_LIST_COD 2
#define LOBBY_SET_COD 3
#define FINISH_GAME_COD 4


class Game_server : public QTcpServer
{
    Q_OBJECT
    void send_data_positoin_to_client(const qint32 id, const qint8, const qint8, QTcpSocket*);
    void send_lobbies_list(QTcpSocket*);
    void handle_reqests(const qint8 cod, QDataStream& in, QTcpSocket *sc);
    void send_error(QTcpSocket *sc);
    void send_figure_to_client(const QChar, QTcpSocket *sc);
    void send_winned_figure(int id);
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
