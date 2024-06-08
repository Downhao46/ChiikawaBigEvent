#ifndef PLAYER_H
#define PLAYER_H

#include"gameobject.h"
#include<QMediaPlayer>
#include<QAudioOutput>

class Player : public GameObject
{
    Q_OBJECT
public:
    Player();

    void picUpdate();

    int getHP(){return mHP;}
    int getMaxHP(){return maxHP;}
    qreal getSpeed(){return mSpeed;}
    QPointF getPos();
    int getAttackInterval();
    int getHPRecovery(){return mHPRecovery;}
    int getRecoveryInterval();
    void HPRecoverControl();
    void HPRecover();
    qreal getHPPlunder(){return mHPPlunder;}
    void canPlunder();//判断吸血
    int getAttackPoint(){return mAttackPoint;}
    int getDefence(){return mDefence;}
    qreal getAttackRatio(){return mAttackRatio;}
    int getAttackSpeed(){return mAttackSpeed;}
    qreal getSpeedRatio(){return mSpeedRatio;}
    qreal getEXPRatio(){return mEXPratio;}
    int getRecessionIndex(){return recessionIndex;}
    int getBloodAttack(){return bloodAttack;}


    void playerShoot(QPointF _dir);
    //void shootSound();

    //音效
    QMediaPlayer *SFXshoot = nullptr;
    QAudioOutput *audiooutputShoot = nullptr;
    QMediaPlayer *SFXhurt = nullptr;
    QAudioOutput *audiooutputHurt = nullptr;

    void setFaceDir(bool _fac);
    bool getFaceDir(){return faceDir;}

    void getHurt(int _attack);
    void PlayerGetExp(int _val);
    int getPlayerExp(){return mExp;}
    int getPlayerLevel(){return mLevel;}
    void LevelBeUp(){mLevel ++; mExp -= 100;mHP++;maxHP++;}
    void getItem(int num);

    static int pixStatus;//0,1,2

    bool isInvincible = 0;//是否无敌
    QTimer* InvincibleTimer = nullptr;

    void resetPlayer();//重置角色

signals:
    void getExp();
    void LevelUp();
    void isHurt();
    void isDead();

private:
    qreal mSpeed;
    bool faceDir;//0->left 1->right
    int mHP;
    int maxHP;
    int mExp;
    int mLevel;
    int mHPRecovery;
    qreal mHPPlunder;
    int mAttackPoint;//攻击力
    int mDefence;//防御力
    qreal mAttackRatio;//攻击倍率
    int mAttackSpeed;//攻击速度
    qreal mSpeedRatio;//移速加成
    qreal mEXPratio;//经验倍率

    int mBulletNum = 1;//子弹个数
    int mExtraBullet = 0;//额外子弹

    int InvincibleTimes = 0;//无敌次数
    int recessionIndex = 0;//击退系数
    int bloodAttack = 0;



    QTimer* HPRecoveryTimer;



};

#endif // PLAYER_H
