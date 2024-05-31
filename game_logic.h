#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include <QString>
#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <functional>

#define ERROR_COD 0
#define POSITION_COD 1
#define LOBBIES_LIST_COD 2
#define LOBBY_SET_COD 3

class Game_Client : public QObject
{
    Q_OBJECT
    QByteArray data;
    int tmp_lobby_id;
    void handle_reqest(const qint8 cod, QDataStream&);
    bool my_move = false;

public:
    Game_Client();
    Game_Client(const char);

    bool is_my_move() const;
    int get_id() const;
    int get_new_pos() const;
    int get_del_pos() const;
    QChar get_current_game_subbol() const;
    QChar get_game_subbol() const;
    int get_new_lobbie_id() const;

    void set_id(const qint8);

    void send_pos_to_server(const qint8 new_pos, const qint8 del_pos);
    void send_lobbies_reqest();
    QString get_new_and_del_position;
signals:
    void new_figure_position_from_server();
    void new_lobbie();
    void new_figure();
    void clear_map();
protected slots:

    void set_char_on_pos_from_server();
    void read_server();

protected:
    qint8 new_pos, del_pos;
    qint32 id;
    void connect_with_server();
    QTcpSocket *socket;
    QChar current_figure = 'X';
    QChar enemy_figure = 'O';

};

#endif // GAME_LOGIC_H
