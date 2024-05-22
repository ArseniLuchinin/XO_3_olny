#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include <QString>
#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

class Game_Client : public QObject
{
    Q_OBJECT
    QByteArray data;
public:
    Game_Client();
    Game_Client(const char);

    int get_id() const;
    int get_new_pos() const;
    int get_del_pos() const;
    char get_game_subbol();

    void send_pos_to_server(const int new_pos, const int del_pos);
    QString get_new_and_del_position;
signals:
    void new_figure_position_from_server();
protected slots:

    void set_char_on_pos_from_server();
    void read_server();

protected:
    int id, new_pos, del_pos;
    void connect_with_server();
    QTcpSocket *socket;
    const char current_figure = 'X';

};

#endif // GAME_LOGIC_H
