#include "game_lobby.h"

Game_lobby::Game_lobby()
{
    for(int i = 0; i < 2; ++i){
        client_sockets[i] = nullptr;
    }
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
