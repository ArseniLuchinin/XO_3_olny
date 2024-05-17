#include "xo_button.h"

XO_Button::XO_Button() : QPushButton(nullptr)
{

}
XO_Button::XO_Button(QWidget *parent) : QPushButton(parent)
{

}

void XO_Button::set_index(const int i){
    index = i;
}

int XO_Button::get_index() const{
    return index;
}
