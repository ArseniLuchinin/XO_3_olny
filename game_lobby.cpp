#include "game_lobby.h"

Game_lobby::Game_lobby()
{
    for(int i = 0; i < 2; ++i){
        users[i].socket = nullptr;
    }

    user_cont = 0;
    users[0].figure = 'X';
    users[1].figure = 'O';

    for(char& p : game_map){
        p = ' ';
    }

}

bool Game_lobby::is_ful() const{
    for(int i = 0; i < 2; ++i){
        if(users[i].socket == nullptr){
            return false;
        }
    }
    return true;
}

Game_lobby::~Game_lobby(){
    for(int i = 0; i < 2; ++i){
        users[i].socket = nullptr;
    }
}

void Game_lobby::add_user(QTcpSocket *n){
    users[user_cont++].socket = n;

}

void Game_lobby::add_position(const int8_t new_pos, const int8_t del_pos){
    game_map[new_pos] = current_char;
    game_map[del_pos] = ' ';
    check_winner();
}

void Game_lobby::check_winner(){

}

QTcpSocket* Game_lobby::get_current_gamer_socket() const{
    return users[0].socket;
}
