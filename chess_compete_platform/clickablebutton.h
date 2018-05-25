#ifndef CLICKABLEBUTTON_H
#define CLICKABLEBUTTON_H

#include <QLabel>

class ClickableButton : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableButton(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent* event);


signals:
    void clicked();


public slots:


};

#endif // CLICKABLEBUTTON_H
