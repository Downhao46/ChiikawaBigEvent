#include "playerbullet.h"
#include"gamewidget.h"


playerBullet::playerBullet(Player *_player, QPointF _dir,int _Attack, qreal _speed)
{
    mPlayer = _player;
    mAttackPoint = _Attack;
    //qDebug()<<mAttackPoint;
    mSpeed = _speed;

    this->setPixmap(QPixmap(":/icons/img/bulletsample.png"));
    this->setScale(0.5);
    mPos = mPlayer->getCenterPos() - QPointF(this->pixmap().width()*scale()/2,this->pixmap().height()*scale()/2);
    this->setPos(mPos);


    mDir = Bullet::MouseDir;
    moveDir = _dir;

}

playerBullet::playerBullet(Player *_player, BulletDir _dir, int _Attack, qreal _speed)
{
    mPlayer = _player;
    mAttackPoint = _Attack;
    qDebug()<<mAttackPoint;
    mSpeed = _speed;
    //mSpeed = 3;

    this->setPixmap(QPixmap(":/icons/img/bulletsample.png"));
    this->setScale(0.5);
    mPos = mPlayer->getCenterPos() - QPointF(this->pixmap().width()*scale()/2,this->pixmap().height()*scale()/2);
    this->setPos(mPos);


    mDir = _dir;
}
