#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include <QString>
#include <QObject>
#include <QTcpSocket>

class Game_Client : public QObject
{
    Q_OBJECT
public:
    Game_Client();
    Game_Client(const char);


    void send_pos_to_server(const QString);
    QString get_new_and_del_position;
signals:
    void new_figure_position_from_server();
protected slots:
    void set_char_on_pos_from_server();
    void read_server();

protected:
    void connect_with_server();
    QTcpSocket *socket;
    const char current_figure = 'X';

};

#endif // GAME_LOGIC_H
