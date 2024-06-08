#ifndef BULLET_H
#define BULLET_H

#include"gameobject.h"



class Bullet : public GameObject
{


public:
    Bullet();
    Bullet(GameObject* _owner);
    virtual ~Bullet(){}

    qreal getSpeed(){return mSpeed;}
    QPointF getMoveDir(){return moveDir;}
    int getAttackPoint(){return mAttackPoint;}

    void BulletMove();

    enum BulletDir{
        DirN,//北南西东
        DirS,
        DirW,
        DirE,
        DirNW,//西北，东北，西南，东南
        DirNE,
        DirSW,
        DirSE,
        MouseDir
    };


protected:



    GameObject* mOwner;
    qreal mSpeed;
    int mAttackPoint;
    QPointF mPos;
    BulletDir mDir;
    QPointF moveDir = QPointF(1,0);


};

#endif // BULLET_H
