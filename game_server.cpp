#include "game_server.h"
#include <QDataStream>


Game_server::Game_server()
{
    if(this->listen(QHostAddress::LocalHost, 123)){
        qDebug() << "Serever is started";
        for(int i = 0; i < 5; ++i)
            lobbies.append(new Game_lobby());
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

    sockets.append(QSharedPointer<QTcpSocket>{socket});
    qDebug() << "New connect: " << socket->socketDescriptor();

}
void Game_server::read_request(){
    socket = (QTcpSocket*)(sender());
    QDataStream in{socket};
    in.setVersion(QDataStream::Qt_5_9);
    if(in.status() == QDataStream::Ok){
        qint8 new_pos, del_pos, cod;
        qint32 id;
        in >> cod;
        qDebug() << "Cod: " << cod;
        //TODO: сделать нормальный метод
        switch (cod) {
            case SEND_LOBBIES_COD:
                send_lobbies_list();
                break;
            case SEND_POS_COD:
                in >> id >> new_pos >> del_pos;
                qDebug() << "add:" << id << new_pos << ' ' << del_pos;
                send_data_positoin_to_client(id, new_pos, del_pos);
                break;
        }
        // switch

    }
    else{
        qDebug() << "Client Date Error";
    }
}

void Game_server::send_data_positoin_to_client(const qint32 id, const qint8 n, const qint8 d){
    data.clear();
    QDataStream out{&data, QIODevice::WriteOnly};
    out.setVersion(QDataStream::Qt_5_9);
    qDebug() << "send to client" << n << ' ' << d;
    out << qint8{SEND_POS_COD} << id << n << d;
    socket = sockets[0].data();
    socket->write(data);
}

void Game_server::send_lobbies_list(){
    data.clear();
    QDataStream out{&data, QIODevice::WriteOnly};
    out.setVersion(QDataStream::Qt_5_9);
    out << qint8{SEND_LOBBIES_COD};
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
    socket->write(data);
}
