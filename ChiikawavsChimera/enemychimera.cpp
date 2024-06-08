#include "enemychimera.h"
#include "gamewidget.h"

enemyChimera::enemyChimera(Player *_player, int _HP, int _AttackPoint, qreal _Speed, int _exp)
    :EnemyBase(_player,_HP,_AttackPoint,_Speed,_exp)
{
    this->setPixmap(QPixmap(":/roles/img/roles/chimera2.png"));
    this->setScale(0.18);
    //expDropped = 50;
    mNo = 2;

    skillTimer = new QTimer(this);

    skillTimer->start(3000);
    connect(skillTimer,&QTimer::timeout,this,&enemyChimera::startSkill);
    // connect(GameWidget::widget,&GameWidget::gamePause,skillTimer,&QTimer::stop);
    // connect(GameWidget::widget,&GameWidget::gameContinue,[this](){
    //     skillTimer->start(3000);
    // });

    //设置特效音
    SFXplayer = new QMediaPlayer(this);
    audiooutput = new QAudioOutput(this);
    audiooutput->setVolume(0.8);
    SFXplayer->setAudioOutput(audiooutput);
    SFXplayer->setSource(QUrl("qrc:/sfx/sounds/chimeraSFX.MP3"));

}

void enemyChimera::setMirrorPixmap()
{
    EnemyBase::setMirrorPixmap();
}

void enemyChimera::startSkill()
{
    if(!GameWidget::widget->isRunning) return ;
    for(int i=0;i<50;i++)
    {
        this->enemyMove();
    }
    SFXplayer->play();
}
