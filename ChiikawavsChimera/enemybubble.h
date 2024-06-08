#ifndef ENEMYBUBBLE_H
#define ENEMYBUBBLE_H

#include"enemybase.h"


class enemyBubble : public EnemyBase
{
public:
    enemyBubble(Player* _player, int _HP, int _AttackPoint, qreal _Speed, int _exp);

    void setMirrorPixmap();

    void startSkill();

private:
    int cnt = 0;
    int skillCnt = 0;
};

#endif // ENEMYBUBBLE_H
