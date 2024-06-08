#include "enemyboss.h"
#include"gamewidget.h"
#include"enemybullet.h"

enemyBoss::enemyBoss(Player *_player, int _HP, int _AttackPoint, qreal _Speed, int _exp)
    :EnemyBase(_player,_HP,_AttackPoint,_Speed,_exp)
{
    this->setPixmap(QPixmap(":/roles/img/roles/chimera5.png"));
    this->setScale(0.2);
    mNo = 5;

    skillTimer = new QTimer(this);

    skillTimer->start(1500);
    connect(skillTimer,&QTimer::timeout,this,&enemyBoss::startSkill);

    //设置特效音
    SFXplayer = new QMediaPlayer(this);
    audiooutput = new QAudioOutput(this);
    SFXplayer->setAudioOutput(audiooutput);
    SFXplayer->setSource(QUrl("qrc:/sfx/sounds/bossSFX.ogg"));
}

void enemyBoss::getHurt(int _attack)
{
    EnemyBase::getHurt(_attack);
    mSpeed += 0.02;
}

void enemyBoss::enemyMove(bool dir)
{
    if(dir) return;
    if(y() == 100)
    {
        setDir(1);
        moveBy(mSpeed,0);
        if(x()>790) this->setX(790);
    }
    if(x() == 790)
    {
        setDir(0);
        moveBy(0,mSpeed);
        if(y()>580) this->setY(580);
    }
    if(y() == 580)
    {
        setDir(0);
        moveBy(-mSpeed,0);
        if(x()<0) this->setX(0);
    }
    if(x() == 0)
    {
        setDir(1);
        moveBy(0,-mSpeed);
        if(y()<100) this->setY(100);
    }
}

void enemyBoss::setMirrorPixmap()
{
    EnemyBase::setMirrorPixmap();
}

void enemyBoss::startSkill()
{
    if(!GameWidget::widget->isRunning) return ;
    //qDebug()<<"skill";
    int _attack =  GameWidget::widget->getPlayer()->getMaxHP() * mAttackPoint * mSpeed ;//攻击力计算
    qreal _speed = 6 * pow(1.1,skillCnt) > 12 ? 12 : 6 * pow(1.1,skillCnt);
    for(int i=0;i<1;i++)
    {
        auto* enemyBT = new enemyBullet(this,Bullet::MouseDir,_attack,_speed,1);
        GameWidget::widget->getGameScene().addItem(enemyBT);
        GameWidget::widget->mEnemyBulletList.append(enemyBT);
    }
    SFXplayer->play();
    skillCnt++;
}
