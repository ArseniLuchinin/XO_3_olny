#include "game_server.h"
#include <QDataStream>


Game_server::Game_server()
{
    if(this->listen(QHostAddress::Any, 123)){
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

    QByteArray d;

    QDataStream to_client{&d, QIODevice::WriteOnly};
    to_client.setVersion(QDataStream::Qt_5_9);
    to_client << "con";
    socket->write(d);
    sockets.append(QSharedPointer<QTcpSocket>{socket});
}

void Game_server::read_request(){

}
