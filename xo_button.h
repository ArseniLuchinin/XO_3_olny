#ifndef XO_BUTTON_H
#define XO_BUTTON_H
#include <qpushbutton.h>

class XO_Button : public QPushButton
{
    Q_OBJECT
    bool selected = false;
public:
    XO_Button();
    XO_Button(QWidget *parent);
    void set_index(const int i);
    int get_index() const;
    bool is_select() const;
    void select(const QString);
    void unselect();
protected:
    int index;
};

#endif // XO_BUTTON_H
