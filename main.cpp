#include <QCoreApplication>
#include "game_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Game_server server{};
    return a.exec();
}
