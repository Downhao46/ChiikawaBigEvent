#include "enemybase.h"


EnemyBase::EnemyBase(GameObject *parent)
    : GameObject{parent}
{}

EnemyBase::~EnemyBase()
{

}

EnemyBase::EnemyBase(Player* _player, int _HP, int _AttackPoint, qreal _Speed,int _exp)
{
    mPlayer = _player;
    mHP = _HP;
    mAttackPoint = _AttackPoint;
    mSpeed = _Speed;
    expDropped = _exp;
}

void EnemyBase::setMirrorPixmap()
{
    //:/roles/img/roles/chimera1.png
    QString address = ":/roles/img/roles/chimera";
    address += QString::number(mNo);
    if(mMoveDir == mFaceDir) return;
    if(mMoveDir  && !mFaceDir)
    {
        address += "-mir";
        mFaceDir = 1;
    }
    else mFaceDir = 0;
    address += ".png";
    this->setPixmap(QPixmap(address));

}

void EnemyBase::getHurt(int _attack)
{
    mHP -= _attack;
    if(mPlayer->getBloodAttack())
    {
        mHP *= pow(0.95,mPlayer->getBloodAttack());
    }
    if(mPlayer->getRecessionIndex())
    {
        int times = mPlayer->getRecessionIndex()*10;
        for(int i=0;i<times;i++)
            enemyMove(1);
    }
}



void EnemyBase::enemyMove(bool dir)
{
    QPointF playerPos = mPlayer->getCenterPos();
    QPointF moveDir = playerPos - this->getCenterPos();
    qreal _x = moveDir.x();
    qreal _y = moveDir.y();
    _x = QString::number(_x,'f',2).toDouble();
    _y = QString::number(_y,'f',2).toDouble();
    if(_x >= 0) setDir(1);
    else setDir(0);
    qreal _r = qSqrt(qPow(_x,2) + qPow(_y,2));
    if(_r == 0) return;
    //保留两位小数
    _r = QString::number(_r,'f',2).toDouble();
    qreal vx = _x/_r * mSpeed;
    qreal vy = _y/_r * mSpeed;
    if(!dir)
        this->moveBy(vx,vy);
    else
        this->moveBy(-vx/mSpeed,-vy/mSpeed);
}

void EnemyBase::startSkill()
{

}
