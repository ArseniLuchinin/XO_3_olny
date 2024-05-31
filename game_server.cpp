#include "game_server.h"
#include <QDataStream>


Game_server::Game_server()
{
    if(this->listen(QHostAddress::LocalHost, 123)){
        qDebug() << "Serever is started";
        for(int i = 0; i < 5; ++i){
            lobbies.append(new Game_lobby());
        }
    }
    else{
        qDebug() << "Server error";
    }
}

void Game_server::incomingConnection(qintptr handle){
    socket = new QTcpSocket();
    socket->setSocketDescriptor(handle);
    connect(socket, &QTcpSocket::readyRead, this, &Game_server::read_request);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    qDebug() << "New connect: " << socket->socketDescriptor();

}
void Game_server::read_request(){
    socket = (QTcpSocket*)(sender());
    QDataStream in{socket};
    in.setVersion(QDataStream::Qt_5_9);
    if(in.status() == QDataStream::Ok){
        qint8 cod;
        in >> cod;
        //qDebug() << "Received cod: " << cod;
        handle_reqests(cod, in, socket);
        // switch

    }
    else{
        qDebug() << "Client Date Error";
    }
}



void Game_server::handle_reqests(const qint8 cod, QDataStream& in, QTcpSocket* sc){
    qint8 new_pos, del_pos;
    qint32 id;
    switch (cod) {
        case LOBBIES_LIST_COD:
            send_lobbies_list(socket);
        break;

        case POSITION_COD:
            in >> id >> new_pos >> del_pos;
            //qDebug() << "add:" << id << new_pos << ' ' << del_pos;
            lobbies[id]->add_position(new_pos, del_pos);
            if(lobbies[id]->check_winner(new_pos%3, new_pos/3) == 3){
                qDebug() << "Winner: " << lobbies[id]->get_current_index();
                send_winned_figure(id);
                break;
            }
            //send_move(id);
            send_data_positoin_to_client(id, new_pos, del_pos, lobbies[id]->get_gamer_socket_at_index(0));
            send_data_positoin_to_client(id, new_pos, del_pos, lobbies[id]->get_gamer_socket_at_index(1));
            lobbies[id]->set_next_gamer_index();
        break;

        case LOBBY_SET_COD:
            in >> id;
            if(!lobbies[id]->is_ful()){
                lobbies[id]->add_user(sc);
                send_figure_to_client(lobbies[id]->get_current_gamer_figure(), sc);
                lobbies[id]->set_next_gamer_index();
            }
            else{
                send_error(sc);
            }
        break;
    }
}

void Game_server::send_figure_to_client(const QChar figure, QTcpSocket* sc){
    data.clear();
    QDataStream out{&data, QIODevice::WriteOnly};
    out.setVersion(QDataStream::Qt_5_9);
    out << qint8{LOBBY_SET_COD} << figure;
    //qDebug() << "Cod:" << SEND_LOBBY_SET_COD;
    sc->write(data);
}

void Game_server::send_winned_figure(int id){
    data.clear();
    QDataStream out{&data, QIODevice::WriteOnly};
    out.setVersion(QDataStream::Qt_5_9);
    out << qint8{FINISH_GAME_COD} << lobbies[id]->get_current_gamer_figure();

    lobbies[id]->get_gamer_socket_at_index(0)->write(data);
    lobbies[id]->get_gamer_socket_at_index(1)->write(data);
}

void Game_server::send_error(QTcpSocket* sc){
    data.clear();
    QDataStream out{&data, QIODevice::WriteOnly};
    out.setVersion(QDataStream::Qt_5_9);
    out << qint8{ERROR_COD};
    sc->write(data);
}

void Game_server::send_data_positoin_to_client(const qint32 id, const qint8 n, const qint8 d, QTcpSocket* sc){
    data.clear();
    QDataStream out{&data, QIODevice::WriteOnly};
    out.setVersion(QDataStream::Qt_5_9);
    //qDebug() << "send to client" << n << ' ' << d;

    out << qint8{POSITION_COD} << id << n << d;
    sc->write(data);
}

void Game_server::send_lobbies_list(QTcpSocket* sc){
    data.clear();
    QDataStream out{&data, QIODevice::WriteOnly};
    out.setVersion(QDataStream::Qt_5_9);
    out << qint8{LOBBIES_LIST_COD};
    qint32 h = 0;
    out << qint32{h};
    for(int i = 0; i < lobbies.length(); ++i){
        if(!lobbies[i]->is_ful()){
            out << qint32{i};
            ++h;
        }
    }
    out.device()->seek(1);
    out << h;
    sc->write(data);
}
