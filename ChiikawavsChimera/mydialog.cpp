#include "mydialog.h"

myDialog::myDialog(QWidget *parent)
    : QDialog{parent}
{
    this->resize(400,400);
    view.setParent(this);
    view.setSceneRect(QRect(0,0,400,400));
    scene.setSceneRect(QRect(0,0,400,400));
    scene.addPixmap(QPixmap(":/ui/img/ui/details.png"));
    view.setScene(&scene);

}
