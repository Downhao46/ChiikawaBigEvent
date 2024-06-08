#include "enemybullet.h"
#include"gamewidget.h"

enemyBullet::enemyBullet(EnemyBase *_owner, BulletDir _dir, int _Attack, qreal _speed,int _type)
{
    mOwner = _owner;
    mAttackPoint = _Attack;
    //qDebug()<<mAttackPoint;
    mSpeed = _speed;
    type = _type;

    if(type == 0)
    {
        this->setPixmap(QPixmap(":/icons/img/enemybulletsample.png"));
        this->setScale(0.5);
    }
    else if(type == 1)
    {
        QPointF _Dir = GameWidget::widget->getPlayer()->getCenterPos() - mOwner->getCenterPos();
        qreal _x = _Dir.x();
        qreal _y = _Dir.y();
        _x = QString::number(_x,'f',2).toDouble();
        _y = QString::number(_y,'f',2).toDouble();
        qreal _r = qSqrt(qPow(_x,2) + qPow(_y,2));
        if(_r == 0) return;
        //保留两位小数
        _r = QString::number(_r,'f',2).toDouble();
        qreal dx = _x/_r;
        qreal dy = _y/_r;
        dx = QString::number(dx,'f',2).toDouble();
        dy = QString::number(dy,'f',2).toDouble();

        moveDir = QPointF(dx,dy);
        this->setPixmap(QPixmap(":/icons/img/bomb.png"));
        this->setScale(0.2);
    }
    mPos = mOwner->getCenterPos() - QPointF(this->pixmap().width()*scale()/2,this->pixmap().height()*scale()/2);
    this->setPos(mPos);


    mDir = _dir;
}
