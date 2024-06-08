#include "bullet.h"

Bullet::Bullet() {}

Bullet::Bullet(GameObject* _owner)
{
    mOwner = _owner;
}

void Bullet::BulletMove()
{
    switch(mDir)
    {
    case DirN:this->moveBy(0,-getSpeed());break;
    case DirS:this->moveBy(0,getSpeed());break;
    case DirW:this->moveBy(-getSpeed(),0);break;
    case DirE:this->moveBy(getSpeed(),0);break;
    case DirNW:this->moveBy(-getSpeed()/sqrt(2),-getSpeed()/sqrt(2));break;
    case DirNE:this->moveBy(getSpeed()/sqrt(2),-getSpeed()/sqrt(2));break;
    case DirSW:this->moveBy(-getSpeed()/sqrt(2),getSpeed()/sqrt(2));break;
    case DirSE:this->moveBy(getSpeed()/sqrt(2),getSpeed()/sqrt(2));break;
    case MouseDir:
    {
        this->moveBy(getSpeed()*getMoveDir().x(),getSpeed()*getMoveDir().y());
    }
    }
    this->show();
}


