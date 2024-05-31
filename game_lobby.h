#ifndef GAME_LOBBY_H
#define GAME_LOBBY_H


#include <QTcpSocket>
#include <QSharedPointer>

typedef struct{
    char figure;
    QTcpSocket* socket;
} user;


class Game_lobby
{

private:
    void print_debug_map();

    int8_t user_conter;
    user users[2];
    QChar game_map[9];

public:
    int8_t check_winner(const int, const int);
    void set_next_gamer_index();
    void add_position(const int8_t, const int8_t);
    int get_current_index() const;
    bool is_ful() const;
    Game_lobby();
    void add_user(QTcpSocket*);
    QTcpSocket* get_current_gamer_socket() const;
    QTcpSocket* get_gamer_socket_at_index(const qint8 ) const;
    QChar get_current_gamer_figure() const;
    ~Game_lobby();
};

#endif // GAME_LOBBY_H
