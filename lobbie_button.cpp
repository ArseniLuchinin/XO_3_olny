#include "lobbie_button.h"

Lobby_button::Lobby_button(const qint32 id,  QWidget *parent) : QPushButton(parent)
{
    set_lobby_id(id);
}

Lobby_button::Lobby_button(const qint32 id, const QString name, QWidget *parent) : QPushButton(name, parent)
{
    set_lobby_id(id);
}


void Lobby_button::set_lobby_id(const qint32 id){
    lobby_id = id;
}

qint32 Lobby_button::get_lobby_id() const{
    return lobby_id;
}

