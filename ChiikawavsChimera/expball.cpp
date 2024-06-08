#include "expball.h"
#include "gamewidget.h"

ExpBall::ExpBall(int _value, QPointF _pos)
{
    expValue = _value;
    this->setPixmap(QPixmap(":/icons/img/expball.png"));
    this->setScale(0.1);
    this->setPos(_pos);

    moveSpeed = 5;
}

void ExpBall::expBallMove()
{
    QPointF playerPos = GameWidget::widget->getPlayer()->getCenterPos();
    QPointF moveDir = playerPos - this->getCenterPos();
    qreal _x = moveDir.x();
    qreal _y = moveDir.y();
    _x = QString::number(_x,'f',2).toDouble();
    _y = QString::number(_y,'f',2).toDouble();
    qreal _r = qSqrt(qPow(_x,2) + qPow(_y,2));
    if(_r == 0) return;
    //保留两位小数
    _r = QString::number(_r,'f',2).toDouble();
    qreal vx = _x/_r * moveSpeed;
    qreal vy = _y/_r * moveSpeed;
    this->moveBy(vx,vy);
}
