#include "game_lobby.h"

Game_lobby::Game_lobby()
{
    for(int i = 0; i < 2; ++i){
        users[i].socket = nullptr;
    }

    user_conter = -1;
    users[0].figure = 'X';
    users[1].figure = 'O';

    for(int i = 0; i < 9; ++i){
        game_map[i] = '_';
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
    users[++user_conter].socket = n;

}

QChar Game_lobby::get_current_gamer_figure() const{
    return users[user_conter].figure;
}

void Game_lobby::add_position(const int8_t new_pos, const int8_t del_pos){
    user_conter = get_current_gamer_index();
    game_map[new_pos] = current_char;
    //game_map[del_pos] = '_';
    if(check_winner(new_pos%3, new_pos/3) == 3){
        qDebug() << "Winner: " << user_conter;
    }
}

void Game_lobby::print_debug_map(){
    qDebug() << "____________________";
    for(int i = 0; i < 3; ++i){
        qDebug() << game_map[i*3] << ' ' << game_map[i*3 + 1] << ' ' << game_map[i*3 + 2];
    }
}

qint8 Game_lobby::get_current_gamer_index(){
    int bit = (++user_conter >> 0) & 1;
    return bit;
}

int Game_lobby::get_current_index() const{
    return user_conter;
}

QTcpSocket* Game_lobby::get_gamer_socket_at_index(const qint8 ind) const{
    return users[ind].socket;
}

int8_t Game_lobby::check_winner(const int cur_pos_x, const int cur_pos_y){
    int counter = 0;
    for(int i = 0; i < 3; ++i){
        if (game_map[cur_pos_y*3 + i] == current_char){
            ++counter;

        }
    }
    if (counter == 3)
        return 3;
    counter = 0;

    for(int i = 0; i < 3; ++i){
        if (game_map[cur_pos_x + i*3] == current_char){
            ++counter;
        }
    }
    if (counter == 3)
        return 3;


    counter = 0;

    for(int i = 0; i < 3; ++i){
        if (game_map[i*3 + i*1] == current_char){
            ++counter;
        }
    }
    if (counter == 3)
        return 3;

    for(int i = 0; i < 3; ++i){
        if (game_map[2 + i*3 - i*1] == current_char){
            ++counter;
        }
    }
    if (counter == 3)
        return 3;

    return 0;
}

QTcpSocket* Game_lobby::get_current_gamer_socket() const{
    return users[user_conter].socket;
}
