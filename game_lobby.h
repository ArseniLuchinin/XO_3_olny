#ifndef GAME_LOBBY_H
#define GAME_LOBBY_H
#include <QTcpSocket>
#include <QSharedPointer>

class Game_lobby
{
private:
    char users_quantity;
    QSharedPointer<QTcpSocket> client_sockets[2];
public:
    Game_lobby();
    void set_pos_to_client(const QString &);
    void new_gamer_connect(QTcpSocket*);
    ~Game_lobby();
};

#endif // GAME_LOBBY_H
