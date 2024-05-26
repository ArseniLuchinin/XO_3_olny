#ifndef GAME_LOBBY_H
#define GAME_LOBBY_H


#include <QTcpSocket>
#include <QSharedPointer>
typedef struct{
    QChar figure;
    QTcpSocket* socket;
} user;


class Game_lobby
{
private:
    int8_t user_conter;
    char users_quantity;
    user users[2];
    char game_map[9];
    char current_char;
    void check_winner();
public:
    void add_position(const int8_t, const int8_t);
    bool is_ful() const;
    Game_lobby();
    void add_user(QTcpSocket*);
    QTcpSocket* get_current_gamer_socket() const;
    QChar get_current_gamer_figure();
    ~Game_lobby();
};

#endif // GAME_LOBBY_H
