#include "player.h"
#include"playerbullet.h"
#include"gamewidget.h"


int Player::pixStatus = 0;


Player::Player()
{
    setPixmap(QPixmap(":/roles/img/roles/usagi1.png"));
    mSpeed = 2;
    mExp = 0;
    mLevel = 1;
    mHP = 5;
    maxHP = 5;
    mHPRecovery = 0;//生命再生
    mHPPlunder = 0;//生命窃取
    mAttackPoint = 1;//初始攻击力
    mDefence = 0;//防御力
    mAttackRatio = 0;//攻击倍率
    mAttackSpeed = 0;//攻击速度
    mSpeedRatio = 0;//移速加成
    mEXPratio = 0;//经验倍率
    mBulletNum = 1;//子弹个数
    mExtraBullet = 0;//额外子弹

    InvincibleTimes = 0;//无敌次数
    recessionIndex = 0;//击退系数
    bloodAttack = 0;//生命值扣血

    HPRecoveryTimer = new QTimer(this);
    connect(HPRecoveryTimer,&QTimer::timeout,this,&Player::HPRecover);
    //HPRecoveryTimer->start(this->getRecoveryInterval());

    InvincibleTimer = new QTimer(this);
    connect(InvincibleTimer,&QTimer::timeout,[this](){
        isInvincible = 0;
    });

    //配置人物音效
    //发射音效
    SFXshoot = new QMediaPlayer(this);
    audiooutputShoot = new QAudioOutput(this);
    SFXshoot->setAudioOutput(audiooutputShoot);
    SFXshoot->setSource(QUrl("qrc:/sfx/sounds/effcet_sfx_playershoot.ogg"));
    //触发保命音效
    SFXhurt = new QMediaPlayer(this);
    audiooutputHurt = new QAudioOutput(this);
    SFXhurt->setAudioOutput(audiooutputHurt);
    SFXhurt->setSource(QUrl("qrc:/sfx/sounds/usagiHurtSFX0.MP3"));
}

QPointF Player::getPos()
{
    return pos();
}

int Player::getAttackInterval()
{
    qreal _attackSpeed = mAttackSpeed;
    _attackSpeed /= 80;
    qreal deltaT = GameDefine::OriginalAttackInterval * pow(0.5,_attackSpeed);
    return (int)deltaT < GameDefine::LimitedAttackInterval ? GameDefine::LimitedAttackInterval : (int)deltaT;
}

int Player::getRecoveryInterval()
{
    qreal _Recovery = mHPRecovery;
    _Recovery /= 8;
    qreal deltaT = 10000 * pow(0.5,_Recovery);
    return (int)deltaT;
}

void Player::HPRecoverControl()
{
    if(mHPRecovery > 0)
    {
        HPRecoveryTimer->start(getRecoveryInterval());
    }
    else
    {
        HPRecoveryTimer->stop();
    }
}

void Player::HPRecover()
{
    if(!GameWidget::widget->isRunning || mHP == maxHP) return;
    mHP++;
    GameWidget::widget->resetHPBar();
}

void Player::canPlunder()
{
    int x = QRandomGenerator::global()->bounded(0,100);
    if(x < mHPPlunder*100 && mHP < maxHP)
    {
        mHP += 1;
    }
}

void Player::playerShoot(QPointF _dir)
{
    int _attack =  (int)(getAttackPoint() * (1+getAttackRatio()));//攻击力计算
    if(_attack < 1) _attack = 1;
    qDebug()<<_attack;

    //主子弹

    for(int i=0;i<mBulletNum;i++)
    {
        auto* playerBT = new playerBullet(this,_dir,_attack);
        GameWidget::widget->getGameScene().addItem(playerBT);
        GameWidget::widget->mBulletList.append(playerBT);
        playerBT->setZValue(0.9);
        for(int j=0;j<5 * i;j++)
        {
            playerBT->BulletMove();
            //SFXplayer->play();
        }
    }


    //额外散射子弹
    int _extraNum = mExtraBullet / 2;
    int _extraAttack = _attack/2;
    if(_extraAttack < 1) _extraAttack = 1;
    if(mExtraBullet > 4)
    {
        _extraNum = 2;
        _extraAttack *= pow(1.2,mExtraBullet/2 - 2);
    }
    for(int i=0;i<_extraNum;i++)
    {
        // QPointF dirUpper(_dir.x()*0.996-_dir.y()*0.087,
        //                  _dir.y()*0.996+_dir.x()*0.087);
        // QPointF dirLower(_dir.x()*0.996+_dir.y()*0.087,
        //                  _dir.y()*0.996-_dir.x()*0.087);
        QPointF dirUpper(_dir.x()*0.966-_dir.y()*0.259,
                         _dir.y()*0.966+_dir.x()*0.259);
        QPointF dirLower(_dir.x()*0.966+_dir.y()*0.259,
                         _dir.y()*0.966-_dir.x()*0.259);
        auto* playerBTUpper = new playerBullet(this,dirUpper,_extraAttack);
        GameWidget::widget->getGameScene().addItem(playerBTUpper);
        GameWidget::widget->mBulletList.append(playerBTUpper);
        playerBTUpper->setZValue(0.9);

        auto* playerBTLower = new playerBullet(this,dirLower,_extraAttack);
        GameWidget::widget->getGameScene().addItem(playerBTLower);
        GameWidget::widget->mBulletList.append(playerBTLower);
        playerBTLower->setZValue(0.9);
        for(int j=0;j<5 * i;j++)
        {
            playerBTUpper->BulletMove();
            playerBTLower->BulletMove();
            //SFXplayer->play();
        }

    }
    SFXshoot->setSource(QUrl("qrc:/sfx/sounds/effcet_sfx_playershoot.ogg"));
    SFXshoot->play();
}

void Player::setFaceDir(bool _fac)
{
    faceDir = _fac;
    //qDebug() << faceDir;

}

void Player::getHurt(int _attack)
{
    qreal defen = mDefence;
    defen /= 8;//免伤计算
    int oriHP = mHP;
    mHP -= (int)(_attack *  pow(0.5,defen))==0 ? 1 : (int)(_attack *  pow(0.5,defen));

    if(mHP <=0 && InvincibleTimes > 0)
    {
        InvincibleTimes -= 1;
        mHP = 0;
        mHP += maxHP * 0.8;
        SFXhurt->setSource(QUrl("qrc:/sfx/sounds/usagiHurtSFX0.MP3"));
        audiooutputHurt->setVolume(1);
        SFXhurt->play();
    }
    else if(oriHP - mHP  >= 3)
    {
        SFXhurt->setSource(QUrl("qrc:/sfx/sounds/usagiHurtSFX.MP3"));
        audiooutputHurt->setVolume(0.5);
        SFXhurt->play();
    }
}



void Player::picUpdate()
{
    QString address = ":/roles/img/roles/usagi";
    address += std::to_string((pixStatus)/7+1);
    if(getFaceDir()) address += "-mir";
    if(isInvincible) address += "-invincible";
    address += ".png";

    this->setPixmap(QPixmap(address));
    pixStatus ++;
    pixStatus %= 21;
}

void Player::PlayerGetExp(int _val)
{
    mExp += (int)(_val * (1+getEXPRatio()));
}

void Player::getItem(int num)//获得物品加成
{
    switch(num)
    {
    case 0:
    {
        mHP += 3;
        maxHP += 3;
        mDefence += 2;
        mSpeedRatio -= 0.05;
        InvincibleTimes += 1;
        break;
    }
    case 1:
    {
        mEXPratio += 0.1;
        mHPRecovery += 2;
        break;
    }
    case 2:
    {
        mAttackPoint += 2;
        mAttackRatio += 0.05;
        break;
    }
    case 3:
    {
        mBulletNum += 1;
        mHP -= 5;
        maxHP -= 5;
        if(mHP <= 0)
        {
            mHP = 1;
        }
        if(maxHP <= 0)
        {
            maxHP = 1;
        }
        mDefence -= 3;
        break;
    }
    case 4:
    {
        mAttackPoint += 1;
        mHP += 2;
        maxHP += 2;
        break;
    }
    case 5:
    {
        mAttackPoint += 2;
        mHP += 2;
        maxHP += 2;
        mDefence += 2;
        break;
    }
    case 6:
    {
        mAttackSpeed += 10;
        mHPRecovery += 2;
        mSpeedRatio += 0.03;
        break;
    }
    case 7://柠檬水
    {
        mSpeedRatio += 0.05;
        mHPPlunder += 0.05;
        break;
    }
    case 8:
    {
        mAttackPoint += 2;
        mDefence -= 1;
        mHPPlunder += 0.05;
        break;
    }
    case 9:
    {
        mHP += 3;
        maxHP += 3;
        mHPRecovery += 3;
        mAttackRatio += 0.05;
        break;
    }
    case 10:
    {
        mAttackPoint += 5;
        mAttackRatio += 0.1;
        mAttackSpeed += 10;
        break;
    }
    case 11:
    {
        mEXPratio += 0.15;
        mAttackRatio += 0.05;
        break;
    }
    case 12:
    {
        mAttackPoint += 3;
        mAttackSpeed += 15;
        mDefence -= 2;
        break;
    }
    case 13:
    {
        mDefence += 5;
        mEXPratio -= 0.1;
        break;
    }
    case 14:
    {
        mHP += 4;
        maxHP +=4;
        mHPRecovery += 2;
        break;
    }
    case 15:
    {
        mEXPratio += 0.1;
        mHP += 1;
        maxHP += 1;
        mDefence += 1;
        break;
    }
    case 16:
    {
        mEXPratio += 0.2;
        mAttackSpeed += 10;
        break;
    }
    case 17:
    {
        mAttackRatio += 0.1;
        mHP += 5;
        maxHP += 5;
        mSpeedRatio -= 0.05;
        break;
    }
    case 18:
    {
        mAttackSpeed += 10;
        mDefence += 2;
        break;
    }
    case 19:
    {
        mAttackRatio -= 0.1;
        mExtraBullet += 2;
        mAttackSpeed -= 20;
        break;
    }
    case 20:
    {
        mAttackSpeed += 5;
        mHP += 2;
        maxHP += 2;
        mHPRecovery += 3;
        break;
    }
    case 21:
    {
        mAttackRatio += 0.1;
        mHP += 2;
        maxHP += 2;
        mSpeedRatio += 0.05;
        break;
    }
    case 22:
    {
        bloodAttack += 1;
        mAttackPoint -= 10;
        mAttackRatio -= 0.5;
        mHPPlunder += 0.1;
        break;
    }
    case 23:
    {
        recessionIndex += 1;
        mEXPratio -= 0.2;
        mDefence += 3;
        break;
    }


    }
}

void Player::resetPlayer()
{
    setPixmap(QPixmap(":/roles/img/roles/usagi1.png"));
    mSpeed = 2;
    mExp = 0;
    mLevel = 1;
    mHP = 5;
    maxHP = 5;
    mHPRecovery = 0;//生命再生
    mHPPlunder = 0;//生命窃取
    mAttackPoint = 1;//初始攻击力
    mDefence = 0;//防御力
    mAttackRatio = 0;//攻击倍率
    mAttackSpeed = 0;//攻击速度
    mSpeedRatio = 0;//移速加成
    mEXPratio = 0;//经验倍率
    mBulletNum = 1;//子弹个数
    mExtraBullet = 0;//额外子弹

    InvincibleTimes = 0;
    recessionIndex = 0;
    bloodAttack = 0;

    HPRecoveryTimer->stop();

}
