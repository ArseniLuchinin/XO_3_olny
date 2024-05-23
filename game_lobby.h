#ifndef GAME_LOBBY_H
#define GAME_LOBBY_H
#define SEND_POS_COD 1
#define SEND_LOBBIES_COD 2


#include <QTcpSocket>
#include <QSharedPointer>


class Game_lobby
{
private:
    char users_quantity;
    QSharedPointer<QTcpSocket> client_sockets[2];
public:
    bool is_ful() const;
    Game_lobby();
    void new_user(QTcpSocket);
    ~Game_lobby();
};

#endif // GAME_LOBBY_H
