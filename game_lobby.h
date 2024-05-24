#ifndef GAME_LOBBY_H
#define GAME_LOBBY_H


#include <QTcpSocket>
#include <QSharedPointer>


class Game_lobby
{
private:
    int8_t user_cont;
    char users_quantity;
    QSharedPointer<QTcpSocket> client_sockets[2];
public:
    bool is_ful() const;
    Game_lobby();
    void add_user(QTcpSocket*);
    QTcpSocket* get_current_gamer_socket() const;

    ~Game_lobby();
};

#endif // GAME_LOBBY_H
