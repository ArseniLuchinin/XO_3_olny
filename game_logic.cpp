#include "game_logic.h"

Game_Client::Game_Client()
{
    socket = new QTcpSocket();
    connect(socket, &QTcpSocket::readyRead, this, &Game_Client::read_server);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    connect_with_server();
}

void Game_Client::set_char_on_pos_from_server(){

}

void Game_Client::connect_with_server(){
    socket->connectToHost("127.0.0.1", 123);
}

void Game_Client::read_server(){

}
