#include "game_lobby.h"

Game_lobby::Game_lobby()
{
    for(int i = 0; i < 2; ++i){
        client_sockets[i] = nullptr;
    }

    user_cont = 0;
}

bool Game_lobby::is_ful() const{
    for(int i = 0; i < 2; ++i){
        if(client_sockets[i] == nullptr){
            return false;
        }
    }
    return true;
}

Game_lobby::~Game_lobby(){
    for(int i = 0; i < 2; ++i){
        client_sockets[i]->reset();
    }
}

void Game_lobby::add_user(QTcpSocket *n){
    client_sockets[user_cont++] = QSharedPointer<QTcpSocket>(n);
}

QTcpSocket* Game_lobby::get_current_gamer_socket() const{
    return client_sockets[0].data();
}
