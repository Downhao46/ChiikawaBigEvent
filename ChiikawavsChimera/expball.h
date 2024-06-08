#ifndef EXPBALL_H
#define EXPBALL_H
#include"gameobject.h"

class ExpBall : public GameObject
{
public:
    ExpBall(int _value, QPointF _pos);
    ~ExpBall() {}

    int getVal(){return expValue;}

    void expBallMove();

private:
    int expValue;
    qreal moveSpeed;
};

#endif // EXPBALL_H
