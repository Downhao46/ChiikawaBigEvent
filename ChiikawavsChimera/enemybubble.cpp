#include "enemybubble.h"
#include "gamewidget.h"
#include "enemybullet.h"

enemyBubble::enemyBubble(Player* _player, int _HP, int _AttackPoint, qreal _Speed, int _exp)
    :EnemyBase(_player,_HP,_AttackPoint,_Speed,_exp)
{
    this->setPixmap(QPixmap(":/roles/img/roles/chimera4.png"));
    this->setScale(0.15);
    mNo = 4;

    //mCount = 1;

    skillTimer = new QTimer(this);
    skillTimer->start(400);

    connect(skillTimer,&QTimer::timeout,[this](){
        cnt++;
        cnt %= 10;
        if(cnt == 3) this->startSkill();
        if(cnt >= 3 && cnt<=4)
            this->setPixmap(QPixmap(":/roles/img/roles/chimera4-mir.png"));
        else
            this->setPixmap(QPixmap(":/roles/img/roles/chimera4.png"));
    });

    //设置特效音
    SFXplayer = new QMediaPlayer(this);
    audiooutput = new QAudioOutput(this);
    audiooutput->setVolume(1.4);
    SFXplayer->setAudioOutput(audiooutput);
    SFXplayer->setSource(QUrl("qrc:/sfx/sounds/bubbleSFX.MP3"));

}

void enemyBubble::setMirrorPixmap()
{

}

void enemyBubble::startSkill()
{
    if(!GameWidget::widget->isRunning) return ;
    //qDebug()<<"skill";
    int _attack =  getAttackPoint() ;//攻击力计算
    for(int i=0;i<7;i++)
    {
        auto* enemyBT = new enemyBullet(this,Bullet::BulletDir(i),_attack * pow(1.1,skillCnt) ,5 * pow(1.1,skillCnt));
        enemyBT->setScale(0.5 * pow(1.1,skillCnt));
        GameWidget::widget->getGameScene().addItem(enemyBT);
        GameWidget::widget->mEnemyBulletList.append(enemyBT);
    }
    skillCnt++;
    SFXplayer->play();
}
