#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include <QString>
#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <functional>

#define SEND_POS_COD 1
#define SEND_LOBBIES_COD 2

class Game_Client : public QObject
{
    Q_OBJECT
    QByteArray data;
    int tmp_lobby_id;
    void handle_reqest(const qint8 cod, QDataStream&);

public:
    Game_Client();
    Game_Client(const char);

    int get_id() const;
    int get_new_pos() const;
    int get_del_pos() const;
    char get_game_subbol() const;
    int get_new_lobbie_id() const;

    void set_id(const qint8);

    void send_pos_to_server(const qint8 new_pos, const qint8 del_pos);
    void send_lobbies_reqest();
    QString get_new_and_del_position;
signals:
    void new_figure_position_from_server();
    void new_lobbie();
protected slots:

    void set_char_on_pos_from_server();
    void read_server();

protected:
    qint8 new_pos, del_pos;
    qint32 id;
    void connect_with_server();
    QTcpSocket *socket;
    const char current_figure = 'X';

};

#endif // GAME_LOGIC_H
