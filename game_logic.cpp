#include "game_logic.h"

Game_Client::Game_Client()
{
    socket = new QTcpSocket();
    connect(socket, &QTcpSocket::readyRead, this, &Game_Client::read_server);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    connect_with_server();
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

char Game_Client::get_game_subbol(){
    return current_figure;
}

void Game_Client::set_char_on_pos_from_server(){

}

void Game_Client::send_pos_to_server(const int new_pos, const int del_pos){
    data.clear();
    QDataStream out{&data, QIODevice::WriteOnly};
    out.setVersion(QDataStream::Qt_5_9);
    out << qint32{new_pos};
    socket->write(data);
}

void Game_Client::connect_with_server(){
    socket->connectToHost("127.0.0.1", 123);
}

void Game_Client::read_server(){
    QDataStream in{socket};
    in.setVersion(QDataStream::Qt_5_9);
    if(in.status() == QDataStream::Ok){
        qint32 tmp;
        in >> tmp;
        new_pos = tmp;
        emit new_figure_position_from_server();
    }
    else{
        qDebug() << "Error message";
    }
}
