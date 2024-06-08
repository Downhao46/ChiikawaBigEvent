#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H

#include"enemybase.h"

class enemyBoss : public EnemyBase
{
public:
    enemyBoss(Player* _player, int _HP, int _AttackPoint, qreal _Speed, int _exp);

    void getHurt(int _attack);
    void enemyMove(bool dir = 0);

    void setMirrorPixmap();

    void startSkill();

private:
    int skillCnt = 0;
};

#endif // ENEMYBOSS_H
