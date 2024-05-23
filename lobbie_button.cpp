#include "lobbie_button.h"

lobbie_button::lobbie_button(const qint32 id,  QWidget *parent) : QPushButton(parent)
{
    set_lobby_id(id);
}

lobbie_button::lobbie_button(const qint32 id, const QString name, QWidget *parent) : QPushButton(name, parent)
{
    set_lobby_id(id);
}


void lobbie_button::set_lobby_id(const qint32 id){
    lobby_id = id;
}

qint32 lobbie_button::get_lobby_id() const{
    return lobby_id;
}
