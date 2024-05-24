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

char Game_Client::get_game_subbol() const{
    return current_figure;
}

int Game_Client::get_new_lobbie_id() const{
    return tmp_lobby_id;
}

void Game_Client::set_char_on_pos_from_server(){

}

void Game_Client::set_id(const qint8 di){
    id = di;
    data.clear();
    QDataStream out{&data, QIODevice::WriteOnly};
    out << qint8{SEND_LOBBY_SET_COD} << id;
    socket->write(data);
}


void Game_Client::send_pos_to_server(const qint8 n, const qint8 d){
    data.clear();
    QDataStream out{&data, QIODevice::WriteOnly};
    out.setVersion(QDataStream::Qt_5_9);
    //qDebug() << "send to serv: " << n << " " << d;
    out << qint8{SEND_POS_COD} << id << n << d;
    socket->write(data);
}

void Game_Client::send_lobbies_reqest(){
    data.clear();
    QDataStream out{&data, QIODevice::WriteOnly};
    out.setVersion(QDataStream::Qt_5_9);
    out << qint8{SEND_LOBBIES_COD};
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
        case SEND_LOBBIES_COD:
            qint32 len;
            in >> len;
            for(int i = 0; i < len; ++i){
                in >> tmp_lobby_id;
                emit new_lobbie();
            }
            break;
        case SEND_POS_COD:
            in >> id >> new_pos >> del_pos;
            emit new_figure_position_from_server();
            break;
    }
}
