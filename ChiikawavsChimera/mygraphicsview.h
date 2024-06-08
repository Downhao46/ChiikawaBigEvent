#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include<QGraphicsView>
#include<QMouseEvent>

class myGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit myGraphicsView();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


signals:
};

#endif // MYGRAPHICSVIEW_H
