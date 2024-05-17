#ifndef GAME_LOBBY_H
#define GAME_LOBBY_H
#include <QTcpSocket>

class Game_lobby
{
protected:
    QTcpSocket* socket;
public:
    Game_lobby();
    void setd_pos_to_client(const int new_pos, int del_pos = -1);
};

#endif // GAME_LOBBY_H
