#include "clickablebutton.h"

ClickableButton::ClickableButton(QWidget *parent) :
    QLabel(parent)
{
}

void ClickableButton::mousePressEvent(QMouseEvent* event){
    emit clicked();
}

