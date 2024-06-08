#ifndef ENEMYBASE_H
#define ENEMYBASE_H

#include "gameobject.h"
#include "player.h"
#include<QTimer>
#include<QRandomGenerator>

class EnemyBase : public GameObject
{
    Q_OBJECT
public:
    explicit EnemyBase(GameObject *parent = nullptr);
    virtual ~EnemyBase();
    EnemyBase(Player* _player, int _HP, int _AttackPoint, qreal _Speed, int _exp);


    void setDir(bool right){mMoveDir = right;}
    virtual void setMirrorPixmap();



    virtual void getHurt(int _attack);
    virtual void enemyMove(bool dir = 0);
    int getAttackPoint(){return mAttackPoint;}
    int getHP(){return mHP;}
    int getExpDropped(){return expDropped;}

    //音效
    QMediaPlayer *SFXplayer = nullptr;
    QAudioOutput *audiooutput = nullptr;

    virtual void startSkill();


signals:
    void isHurt();
    void isDead();


protected:
    int mNo;//编号 1：虫 2：奇美拉 3：大强
    bool mMoveDir = 0;
    bool mFaceDir = 0;
    Player* mPlayer;
    int mHP;
    int mAttackPoint;
    qreal mSpeed;
    int expDropped;

    QTimer* skillTimer = nullptr;

    //int cnt = 0;//神秘报错 析构函数需要为虚函数

};

#endif // ENEMYBASE_H
