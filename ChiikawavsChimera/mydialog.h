#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include<QGraphicsView>
#include<QGraphicsScene>

class myDialog : public QDialog
{
public:
    myDialog(QWidget *parent = nullptr);

private:
    QGraphicsView view;
    QGraphicsScene scene;
};

#endif // MYDIALOG_H
