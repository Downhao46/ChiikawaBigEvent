#ifndef ENEMYBIG_H
#define ENEMYBIG_H

#include"enemybase.h"


class enemyBig : public EnemyBase
{
public:
    enemyBig(Player* _player, int _HP, int _AttackPoint, qreal _Speed, int _exp);

    void setMirrorPixmap();

    void startSkill();

private:

};

#endif // ENEMYBIG_H
