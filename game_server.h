#ifndef GAME_SERVER_H
#define GAME_SERVER_H
#include <QTcpServer>

class Game_server : public QTcpServer
{
    Q_OBJECT
protected:
    QTcpSocket *socket;

public:
    Game_server();
};

#endif // GAME_SERVER_H
