#include "game_logic.h"

Game_Client::Game_Client()
{
    socket = new QTcpSocket();
    connect(socket, &QTcpSocket::readyRead, this, &Game_Client::read_server);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    connect_with_server();
    id = 0;
}

int Game_Client::get_id() const{
    return  id;
}
int Game_Client::get_new_pos() const{
    return  new_pos;
}
int Game_Client::get_del_pos() const{
    return del_pos;
}

QChar Game_Client::get_current_game_subbol() const{
    if(my_move){
        return current_figure;
    }
    else{
        return enemy_figure;
    }
}

int Game_Client::get_new_lobbie_id() const{
    return tmp_lobby_id;
}

bool Game_Client::is_my_move() const{
    return my_move;
}

QChar Game_Client::get_game_subbol() const{
    return current_figure;
}

void Game_Client::set_char_on_pos_from_server(){

}

void Game_Client::set_id(const qint8 di){
    id = di;
    data.clear();
    QDataStream out{&data, QIODevice::WriteOnly};
    out << qint8{LOBBY_SET_COD} << id;
    socket->write(data);
}


void Game_Client::send_pos_to_server(const qint8 n, const qint8 d){
    data.clear();
    QDataStream out{&data, QIODevice::WriteOnly};
    out.setVersion(QDataStream::Qt_5_9);
    //qDebug() << "send to serv: " << n << " " << d;
    out << qint8{POSITION_COD} << id << n << d;
    socket->write(data);
}

void Game_Client::send_lobbies_reqest(){
    data.clear();
    QDataStream out{&data, QIODevice::WriteOnly};
    out.setVersion(QDataStream::Qt_5_9);
    out << qint8{LOBBIES_LIST_COD};
    socket->write(data);
}

void Game_Client::connect_with_server(){
    socket->connectToHost("127.0.0.1", 123);
}

void Game_Client::read_server(){
    QDataStream in{socket};
    in.setVersion(QDataStream::Qt_5_9);
    if(in.status() == QDataStream::Ok){
        qint8 cod;
        in >> cod;
        handle_reqest(cod, in);
    }
    else{
        qDebug() << "Error message";
    }
}

void Game_Client::handle_reqest(const qint8 cod, QDataStream& in){
    switch (cod) {
        case LOBBIES_LIST_COD:
            qint32 len;
            in >> len;
            for(int i = 0; i < len; ++i){
                in >> tmp_lobby_id;
                emit new_lobbie();
            }
            break;
        case POSITION_COD:
            in >> id >> new_pos >> del_pos;
            emit new_figure_position_from_server();
            if(my_move){
                my_move = false;
            }else{
                my_move = true;
            }
            break;
        case LOBBY_SET_COD:
            in >> current_figure;
            if(current_figure == 'X'){
                my_move = true;
                enemy_figure = 'O';
            }
            else{
                my_move = false;
                enemy_figure = 'X';
            }
            emit new_figure();
            emit clear_map();
            break;
    }
}

