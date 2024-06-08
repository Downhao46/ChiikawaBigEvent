#ifndef MYBUTTON_H
#define MYBUTTON_H

#include<QToolButton>
#include <QDebug>

class myButton : public QToolButton
{
    Q_OBJECT
public:
    explicit myButton(QWidget *parent = nullptr);
    ~myButton(){}

signals:
};

#endif // MYBUTTON_H
