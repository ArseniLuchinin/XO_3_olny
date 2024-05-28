#ifndef LOBBIE_BUTTON_H
#define LOBBIE_BUTTON_H

#include <QPushButton>
#include <QString>

class lobbie_button : public QPushButton
{
    qint32 lobby_id;

public:
    qint32 get_lobby_id() const;
    void set_lobby_id(const qint32);
    lobbie_button(const qint32, QWidget* = nullptr);
    lobbie_button(const qint32, const QString, QWidget* = nullptr);
};

#endif // LOBBIE_BUTTON_H
