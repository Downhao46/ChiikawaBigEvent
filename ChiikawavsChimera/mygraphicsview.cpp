#include "mygraphicsview.h"
#include"gamewidget.h"

myGraphicsView::myGraphicsView()

{}

void myGraphicsView::mousePressEvent(QMouseEvent *event)
{
    GameWidget::widget->mousePressEvent(event);
}

/*
QGraphicsView默认情况下会截获其包含的QWidget的鼠标事件，
这可能会导致在QWidget上添加的鼠标事件函数无法正常工作。
要解决这个问题，你可以考虑以下几种方法：

重写鼠标事件处理函数：
在QGraphicsView的子类中重新实现鼠标事件处理函数，
然后在这些函数中调用父类的相应函数，并处理事件。
例如，你可以在QGraphicsView的子类中重新实现mouseMoveEvent、
mousePressEvent和mouseReleaseEvent，
然后在这些函数中调用父类的相应函数，以确保QWidget中的事件也能得到正确处理。
*/


void myGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    GameWidget::widget->mouseMoveEvent(event);
}

void myGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    GameWidget::widget->mouseReleaseEvent(event);
}
