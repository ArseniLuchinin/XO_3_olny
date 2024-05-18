#include "game_lobby.h"

Game_lobby::Game_lobby()
{
    for(int i = 0; i < 2; ++i){
        client_sockets[i] = nullptr;
    }
}

Game_lobby::~Game_lobby(){
    for(int i = 0; i < 2; ++i){
        client_sockets[i]->reset();
    }
}
