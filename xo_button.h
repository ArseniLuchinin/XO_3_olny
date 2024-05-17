#ifndef XO_BUTTON_H
#define XO_BUTTON_H
#include <qpushbutton.h>

class XO_Button : public QPushButton
{
    Q_OBJECT
public:
    XO_Button();
    XO_Button(QWidget *parent);
    void set_index(const int i);
    int get_index() const;
protected:
    int index;
};

#endif // XO_BUTTON_H
