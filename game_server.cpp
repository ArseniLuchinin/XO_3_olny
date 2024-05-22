#include "game_server.h"
#include <QDataStream>


Game_server::Game_server()
{
    if(this->listen(QHostAddress::LocalHost, 123)){
        qDebug() << "Serever is started";
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
        qint32 new_pos;
        in >> new_pos;
        send_data_positoin_to_client(new_pos, 1);
    }
    else{
        qDebug() << "Client Date Error\n";
    }
}

void Game_server::send_data_positoin_to_client(const qint32 new_pos, const qint32 del_pos){
    socket = sockets[0].data();
    data.clear();
    QDataStream out{&data, QIODevice::WriteOnly};
    out.setVersion(QDataStream::Qt_5_9);
    out << new_pos;
    socket->write(data);
}
