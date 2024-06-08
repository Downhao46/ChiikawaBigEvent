#include "gamewidget.h"
#include "ui_gamewidget.h"
#include"gamecontrol.h"
#include"mydialog.h"

GameWidget* GameWidget::widget = nullptr;

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    widget =this;
    setWindowTitle("Chiikawaおっきい討伐");
    setWindowIcon(QIcon(":/icons/img/windowicon.png"));
    setFixedSize(900, 700);

    mGameView.setParent(this);
    mGameView.setSceneRect(QRect(0,0,900,700));



    this->Init_Start();


}

GameWidget::~GameWidget()
{
    delete ui;
    //qDebug()<<"widget released";
}

void GameWidget::Init_Start()
{
    mStartScene.setSceneRect(QRect(0,0,900,700));
    //设置背景图
    mStartScene.addPixmap(QPixmap(":/backgrouds/img/StartBackground.png"));

    //按钮音效
    ButtonAudioplayer = new QMediaPlayer(this);
    ButtonAudioOutput = new QAudioOutput(this);
    ButtonAudioplayer->setAudioOutput(ButtonAudioOutput);
    ButtonAudioplayer->setSource(QUrl("qrc:/sfx/sounds/effcet_ui_button.ogg"));

    //开始按钮
    startBtn = new myButton(this);
    startBtn->setAutoRaise(true);
    startBtn->setFixedSize(182,52);
    startBtn->setIcon(QIcon(":/ui/img/ui/startBtn.png"));
    startBtn->setIconSize(QSize(182,52));
    startBtn->move(100,140);

    //记录按钮
    detailBtn = new myButton(this);
    detailBtn->setAutoRaise(true);
    detailBtn->setFixedSize(182,52);
    detailBtn->setIcon(QIcon(":/ui/img/ui/detailBtn.png"));
    detailBtn->setIconSize(QSize(182,52));
    detailBtn->move(100,200);

    connect(detailBtn,&QToolButton::clicked,[this](){
        ButtonAudioplayer->setSource(QUrl("qrc:/sfx/sounds/effcet_ui_button.ogg"));
        ButtonAudioplayer->play();
        myDialog details(this);
        details.exec();
    });

    //退出按钮
    exitBtn = new myButton(this);
    exitBtn->setAutoRaise(true);
    exitBtn->setFixedSize(182,52);
    exitBtn->setIcon(QIcon(":/ui/img/ui/exitBtn.png"));
    exitBtn->setIconSize(QSize(182,52));
    exitBtn->move(100,300);

    connect(exitBtn,&QToolButton::clicked,[this](){
        close();
    });

    //返回主页按钮
    backBtn = new myButton(this);
    backBtn->setAutoRaise(true);
    backBtn->setFixedSize(182,52);
    backBtn->setIcon(QIcon(":/ui/img/ui/backBtn.png"));
    backBtn->setIconSize(QSize(182,52));
    backBtn->move(600,200);
    backBtn->hide();

    connect(backBtn,&QToolButton::clicked,[this](){
        pauseBTN->hide();
        ButtonAudioplayer->setSource(QUrl("qrc:/sfx/sounds/effcet_ui_button.ogg"));
        ButtonAudioplayer->play();
        WinBGMplayer->stop();
        GameOver();
        mGameView.setScene(&mStartScene);
        startBtn->show();
        detailBtn->show();
        restartBtn->hide();
        exitBtn->move(100,300);
        backBtn->hide();
    });


    //重新开始按钮
    restartBtn = new myButton(this);
    restartBtn->setAutoRaise(true);
    restartBtn->setFixedSize(182,52);
    restartBtn->setIcon(QIcon(":/ui/img/ui/onceMoreBtn.png"));
    restartBtn->setIconSize(QSize(182,52));
    restartBtn->hide();

    connect(restartBtn,&QToolButton::clicked,[this](){
        ButtonAudioplayer->setSource(QUrl("qrc:/sfx/sounds/effcet_ui_button.ogg"));
        ButtonAudioplayer->play();
        WinBGMplayer->stop();
        restartGame();
        continueBtn->hide();
        restartBtn->hide();
        backBtn->hide();
    });

    //点击按钮后加载游戏场景
    connect(startBtn,&QToolButton::clicked,[this](){
        //加载游戏场景
        ButtonAudioplayer->setSource(QUrl("qrc:/sfx/sounds/effcet_ui_button.ogg"));
        ButtonAudioplayer->play();
        if(beginTimes == 0)
        {
            Init_Game();
            startBtn->hide();
            detailBtn->hide();
            exitBtn->hide();
        }
        else
        {
            restartGame();
        }
        beginTimes++;
    });



    mGameView.setScene(&mStartScene);
    mGameView.show();

}

void GameWidget::Init_Game()
{


    //设置图片
    mGameScene.setSceneRect(QRect(0,0,900,700));
    mGameScene.addPixmap(QPixmap(":/backgrouds/img/GameBackground.png"));

    mPlayer.setScale(0.15);
    mPlayer.setPos(200,200);
    mPlayer.setZValue(1);
    mGameScene.addItem(&mPlayer);

    //设置光标
    QCursor cursor(QPixmap(":/icons/img/cursor.png"));
    QApplication::setOverrideCursor(cursor);


    //游戏背景音乐

    BGMplayer = new QMediaPlayer(this);
    BGMOutput = new QAudioOutput(this);
    BGMplayer->setAudioOutput(BGMOutput);
    BGMplayer->setSource(QUrl("qrc:/bgm/sounds/gameBGM.MP3"));
    //audiooutput->setVolume(0.2);
    BGMplayer->play();

    BGMTimer = new QTimer(this);
    BGMTimer->start(32000);
    connect(BGMTimer,&QTimer::timeout,[this](){
        BGMplayer->setSource(QUrl("qrc:/bgm/sounds/gameBGM.MP3"));
        BGMplayer->play();
    });

    //胜利音乐配置
    WinBGMplayer = new QMediaPlayer(this);
    WinBGMOutput = new QAudioOutput(this);
    WinBGMplayer->setAudioOutput(WinBGMOutput);
    //WinBGMplayer->setSource(QUrl("qrc:/bgm/sounds/winBGM.mp3"));


    //audiooutput->setVolume(0.2);
    //升级音效
    LevelUPAudioplayer = new QMediaPlayer(this);
    LevelUPAudioOutput = new QAudioOutput(this);
    LevelUPAudioplayer->setAudioOutput(LevelUPAudioOutput);
    LevelUPAudioplayer->setSource(QUrl("qrc:/sfx/sounds/effcet_sfx_levelup.ogg"));

    //开启定时器
    setTimer();
    startTimer();



    mGameView.setScene(&mGameScene);


    //设置暂停按钮
    pauseBTN = new myButton(this);
    pauseBTN->move(874,0);
    pauseBTN->setFixedSize(26,26);
    pauseBTN->setIcon(QIcon(":/icons/img/pausebtn.png"));
    pauseBTN->setIconSize(QSize(26,26));
    //pauseBTN->setAutoRaise(true);
    pauseBTN->show();
    connect(pauseBTN,&QToolButton::clicked,[this](){
        ButtonAudioplayer->setSource(QUrl("qrc:/sfx/sounds/effcet_ui_button.ogg"));
        ButtonAudioplayer->play();

        if(isChoosing)
        {
            return;
        }
        else if(!isStopped)
        {
            stopTimer();
            continueBtn->move(600,260);
            restartBtn->move(600,140);
            backBtn->move(600,200);
            grayBackground = new GameObject();
            grayBackground->setPixmap(QPixmap(":/backgrouds/img/grayBackground.png"));
            grayBackground->setZValue(1.5);
            mGameScene.addItem(grayBackground);
            continueBtn->show();
            restartBtn->show();
            backBtn->show();
            this->isStopped = !this->isStopped;
        }
        else
        {
            startTimer();
            mGameScene.removeItem(grayBackground);
            if(grayBackground != nullptr) delete grayBackground;
            continueBtn->hide();
            restartBtn->hide();
            backBtn->hide();
            this->isStopped = !this->isStopped;
        }

        //

    });


    //继续游戏按钮
    continueBtn = new myButton(this);
    continueBtn->setAutoRaise(true);
    continueBtn->setFixedSize(182,52);
    continueBtn->setIcon(QIcon(":/ui/img/ui/continueBtn.png"));
    continueBtn->setIconSize(QSize(182,52));
    continueBtn->hide();

    connect(continueBtn,&QToolButton::clicked,pauseBTN,&QToolButton::click);

    QFont font("宋体",11,75);

    //设置属性栏
    setProperties();


    //升级获得物品
    connect(&mPlayer,&Player::LevelUp,[this](){

        stopTimer();
        //BGMplayer->play();

        int x=1,y=1,z=1;
        do
        {
            x = QRandomGenerator::global()->bounded(0,GameDefine::TotalItemNum);
            y = QRandomGenerator::global()->bounded(0,GameDefine::TotalItemNum);
            z = QRandomGenerator::global()->bounded(0,GameDefine::TotalItemNum);
        }while(x==y || x== z || y==z);
        opt1 = x;
        opt2 = y;
        opt3 = z;
        if(optBtn1 != nullptr) delete optBtn1;
        if(optBtn2 != nullptr) delete optBtn2;
        if(optBtn3 != nullptr) delete optBtn3;
        optBtn1 = new mySelectiveButton(x,this);
        optBtn2 = new mySelectiveButton(y,this);
        optBtn3 = new mySelectiveButton(z,this);
        optBtn1->move(250,120);
        optBtn2->move(400,120);
        optBtn3->move(550,120);

        connect(optBtn1,&QToolButton::clicked,[this](){

            //获得道具...
            mPlayer.getItem(opt1);
            emit this->isSelected();//发送选择完毕信号 刷新数值显示
        });
        connect(optBtn2,&QToolButton::clicked,[this](){

            //获得道具...
            mPlayer.getItem(opt2);
            emit this->isSelected();
        });
        connect(optBtn3,&QToolButton::clicked,[this](){

            //获得道具...
            mPlayer.getItem(opt3);
            emit this->isSelected();
        });

        optBtn1->show();
        optBtn2->show();
        optBtn3->show();

        //选择道具后继续游戏
        connect(this,&GameWidget::isSelected,[this](){
            ButtonAudioplayer->setSource(QUrl("qrc:/sfx/sounds/effcet_ui_button.ogg"));
            ButtonAudioplayer->play();


            optBtn1->hide();
            optBtn2->hide();
            optBtn3->hide();
            startTimer();
        });

    });


    //连接游戏结束
    connect(&mPlayer,&Player::isDead,[this](){
        this->GameOver();
        HPlabel->hide();
        HPRecoverylabel->hide();
        HPPlunderlabel->hide();
        AttackRatiolabel->hide();
        AttackPointlabel->hide();
        AttackSpeedlabel->hide();
        Defencelabel->hide();
        SpeedRatiolabel->hide();
        EXPRatiolabel->hide();
        pauseBTN->hide();
        HPBar->hide();
        experienceBar->hide();
        LevelLabel->hide();
    });
}

void GameWidget::restartGame()
{
    mGameView.setScene(&mGameScene);
    if(isStopped)
    {
        mGameScene.removeItem(grayBackground);
        if(grayBackground != nullptr) delete grayBackground;
        backBtn->hide();
        continueBtn->hide();
        isStopped = 0;
    }
    startBtn->hide();
    detailBtn->hide();
    exitBtn->hide();

    //重置光标
    QCursor cursor(QPixmap(":/icons/img/cursor.png"));
    QApplication::setOverrideCursor(cursor);

    //重置角色
    mPlayer.resetPlayer();
    mPlayer.setPos(200,200);

    //显示信息
    pauseBTN->show();
    LevelLabel->show();
    LevelLabel->setText(" Lv:1");
    resetHPBar();
    HPBar->show();
    experienceBar->show();
    experienceBar->setValue(0);
    experienceBar->setFormat(" EXP:0/100");

    //时间重置
    gameClock->show();
    gameClock->display(GameDefine::GameTime);
    resetProperties();
    startTimer();
    BGMplayer->setSource(QUrl("qrc:/bgm/sounds/gameBGM.MP3"));
    BGMplayer->play();
    BGMTimer->start(32000);


    //清除怪物与子弹
    int enemyNum = mEnemyList.size();
    for(int i = enemyNum-1; i >= 0; i--)
    {
        //qDebug()<<"delete enemy";
        mGameScene.removeItem(mEnemyList[i]);
        if(mEnemyList[i] != nullptr) mEnemyList[i]->deleteLater();
        mEnemyList.removeOne(mEnemyList[i]);
    }
    int enemyBulletNum = mEnemyBulletList.size();
    for(int i = enemyBulletNum-1; i >= 0; i--)
    {
        mGameScene.removeItem(mEnemyBulletList[i]);
        if(mEnemyBulletList[i] != nullptr) mEnemyBulletList[i]->deleteLater();
        mEnemyBulletList.removeOne(mEnemyBulletList[i]);
    }
    int playerBulletNum = mBulletList.size();
    for(int i = playerBulletNum-1; i >= 0; i--)
    {
        mGameScene.removeItem(mBulletList[i]);
        if(mBulletList[i] != nullptr) mBulletList[i]->deleteLater();
        mBulletList.removeOne(mBulletList[i]);
    }
    int expBallNum = mExpBallList.size();
    for(int i = expBallNum-1; i >= 0; i--)
    {
        mGameScene.removeItem(mExpBallList[i]);
        if(mExpBallList[i] != nullptr) mExpBallList[i]->deleteLater();
        mExpBallList.removeOne(mExpBallList[i]);
    }

}

void GameWidget::setTimer()
{
    //设置定时器
    playerMoveTimer = new QTimer(this);
    playerShootTimer = new QTimer(this);
    bulletMoveTimer = new QTimer(this);
    playerUpdateTimer = new QTimer(this);
    //enemySummonTimer = new QTimer(this);
    enemyMoveTimer = new QTimer(this);
    connect(playerMoveTimer,&QTimer::timeout,[this](){
        playerMove();//玩家移动
        getExp();//检测获取经验
        player_enemyCollision();
    });
    connect(playerShootTimer,&QTimer::timeout,[this](){
        mPlayer.playerShoot(playerBulletDir);
        //qDebug() << playerBulletDir;
    });
    connect(bulletMoveTimer,&QTimer::timeout,[this](){
        for(auto bullet : mBulletList){
            bullet->Bullet::BulletMove();
        }
        for(auto enemyBullet : mEnemyBulletList){
            enemyBullet->Bullet::BulletMove();
        }
        //检测碰撞
        bullet_enemyCollision();
        bullet_playerCollision();
        //出界检测
        releaseOutBullet();
        releaseOutEnemyBullet();


    });
    connect(playerUpdateTimer,&QTimer::timeout,&mPlayer,&Player::picUpdate);
    // connect(enemySummonTimer,&QTimer::timeout,[this](){
    //     // enemyInsSummon();
    //     // enemyChimeraSummon();

    // });
    connect(enemyMoveTimer,&QTimer::timeout,[this](){
        //testEnemy->enemyMove();
        for(auto enemy : mEnemyList){
            enemy->enemyMove();
            enemy->setMirrorPixmap();//怪物移动与面朝方向
        }
    });

    //设置倒计时

    standardTimer = new QTimer(this);
    gameClock = new QLCDNumber(this);
    gameClock->setFixedSize(80,40);
    gameClock->move(410,35);
    gameClock->display(GameDefine::GameTime);
    gameClock->setStyleSheet("QLCDNumber{padding: 1px;"
                             "color: rgb(255,0,0);"
                             "border-style: solid;"
                             "border: 2px solid black;"
                             "border-radius: 8px;"
                             "width:50px;"
                             "background-color: rgb(255,255,255);}");

    gameClock->setSegmentStyle(QLCDNumber::Flat);

    gameClock->show();

    connect(standardTimer,&QTimer::timeout,[this](){
        int val = this->gameClock->intValue();
        GameControl::Instance()->EnemySummonControl(val);
        if(val <= 0)
        {
            stopTimer();
            GameWin();
        }
        else
        {
            this->gameClock->display(val-1);
        }

    });
}

void GameWidget::startTimer()
{

    isRunning = 1;
    //开启定时器

    playerMoveTimer->start(GameDefine::GameViewUpdateTime);
    bulletMoveTimer->start(GameDefine::GameViewUpdateTime);

    enemyMoveTimer->start(GameDefine::GameViewUpdateTime);

    //enemySummonTimer->start(3000);
    playerUpdateTimer->start(30);

    standardTimer->start(1000);

    //开启音乐
    //BGMplayer->play();
}

void GameWidget::stopTimer()
{
    isRunning = 0;
    //暂停定时器
    playerMoveTimer->stop();
    bulletMoveTimer->stop();
    //enemySummonTimer->stop();
    enemyMoveTimer->stop();
    playerShootTimer->stop();
    playerUpdateTimer->stop();

    standardTimer->stop();

    //暂停音乐
    //BGMplayer->pause();
}

void GameWidget::GameWin()
{
    stopTimer();
    WinBGMplayer->setSource(QUrl("qrc:/bgm/sounds/winBGM.mp3"));
    WinBGMplayer->play();

    BGMTimer->stop();
    BGMplayer->stop();

    pauseBTN->hide();
    HPBar->hide();
    experienceBar->hide();
    LevelLabel->hide();

    HPlabel->hide();
    HPRecoverylabel->hide();
    HPPlunderlabel->hide();
    AttackRatiolabel->hide();
    AttackPointlabel->hide();
    AttackSpeedlabel->hide();
    Defencelabel->hide();
    SpeedRatiolabel->hide();
    EXPRatiolabel->hide();
    //配置结束场景
    gameClock->hide();
    mWinScene.setSceneRect(QRect(0,0,900,700));
    mWinScene.addPixmap(QPixmap(":/backgrouds/img/gamewinBackground.png"));
    winText = new GameObject();
    winText->setPixmap(QPixmap(":/ui/img/ui/winText.png"));
    winText->setScale(0.4);
    mWinScene.addItem(winText);
    continueBtn->hide();
    restartBtn->show();
    restartBtn->move(100,100);
    backBtn->show();
    backBtn->move(100,160);
    exitBtn->show();
    exitBtn->move(100,220);

    //重置光标
    QCursor cursor;
    cursor.setShape(Qt::ArrowCursor);
    QApplication::setOverrideCursor(cursor);

    mGameView.setScene(&mWinScene);
}

void GameWidget::GameOver()
{
    stopTimer();
    BGMTimer->stop();
    BGMplayer->pause();

    HPlabel->hide();
    HPRecoverylabel->hide();
    HPPlunderlabel->hide();
    AttackRatiolabel->hide();
    AttackPointlabel->hide();
    AttackSpeedlabel->hide();
    Defencelabel->hide();
    SpeedRatiolabel->hide();
    EXPRatiolabel->hide();
    HPBar->hide();
    experienceBar->hide();
    LevelLabel->hide();
    //配置结束场景
    gameClock->hide();
    mOverScene.setSceneRect(QRect(0,0,900,700));
    mOverScene.addPixmap(QPixmap(":/backgrouds/img/gameoverBackground.png"));
    loseText = new GameObject();
    loseText->setPixmap(QPixmap(":/ui/img/ui/loseText.png"));
    loseText->setScale(0.4);
    mOverScene.addItem(loseText);
    continueBtn->hide();
    restartBtn->show();
    restartBtn->move(100,100);
    backBtn->show();
    backBtn->move(100,160);
    exitBtn->show();
    exitBtn->move(100,220);

    //重置光标
    QCursor cursor;
    cursor.setShape(Qt::ArrowCursor);
    QApplication::setOverrideCursor(cursor);

    mGameView.setScene(&mOverScene);
}

void GameWidget::resetHPBar()
{
    if(mPlayer.getHP() > 0)
    {
        HPBar->setMaximum(mPlayer.getMaxHP());
        HPBar->setValue(mPlayer.getHP());
        HPBar->setFormat(" HP:"+QString::number(mPlayer.getHP())+"/"+QString::number(mPlayer.getMaxHP()));
    }
    else
    {
        emit mPlayer.isDead();
        HPBar->setValue(0);
        HPBar->setFormat(" HP:0/"+QString::number(mPlayer.getMaxHP()));
    }
}

void GameWidget::playerMove()
{
    qreal speedX = mPlayer.getSpeed()*(1+mPlayer.getSpeedRatio()*2);
    if(mKeyList.size() > 1) speedX /= sqrt(2);
    for(int keyCode : mKeyList)
    {
        switch(keyCode)
        {
        case Qt::Key_W: mPlayer.moveBy(0,-2*speedX);break;
        case Qt::Key_S: mPlayer.moveBy(0,2*speedX);break;
        case Qt::Key_A:
        {   mPlayer.moveBy(-2*speedX,0);
            mPlayer.setFaceDir(0);
            break;
        }
        case Qt::Key_D:
        {mPlayer.moveBy(2*speedX,0);
            mPlayer.setFaceDir(1);
            break;
        }
        }
    }
    if(mPlayer.pos().x()<0)
        mPlayer.setX(0);
    if(mPlayer.pos().y()<100)
        mPlayer.setY(100);
    if(mPlayer.pos().x()>900-mPlayer.scale()*mPlayer.pixmap().width())
        mPlayer.setX(900-mPlayer.scale()*mPlayer.pixmap().width());
    if(mPlayer.pos().y()>700-mPlayer.scale()*mPlayer.pixmap().height())
        mPlayer.setY(700-mPlayer.scale()*mPlayer.pixmap().height());
}


void GameWidget::keyPressEvent(QKeyEvent *event)
{
    //Q键暂停
    if(event->key() == Qt::Key_Q)
    {
        pauseBTN->click();
        // this->isStopped = !this->isStopped;
        // if(this->isStopped) stopTimer();
        // else startTimer();
    }

    switch(event->key())
    {
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
        mKeyList.append(event->key());
        break;
    }

    // QKeyEvent *key=(QKeyEvent*) event;
    // switch(key->key())

    // {
    // case Qt::Key_Up:
    // case Qt::Key_Down:
    // case Qt::Key_Left:
    // case Qt::Key_Right:
    //     mBulletDirList.append(key->key());
    //     break;
    // }
    // //qDebug()<<key->key()<<"is pressed";
}

void GameWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(mKeyList.contains(event->key())){
        mKeyList.removeAll(event->key());
    }

    // if(mBulletDirList.contains(event->key())){
    //     mBulletDirList.removeOne(event->key());
    // }
}

void GameWidget::mousePressEvent(QMouseEvent *event)
{

    if(!isRunning) return;
    isPressed = 1;
    //qDebug()<<"hello";
    playerShootTimer->start(mPlayer.getAttackInterval());


    QWidget::mousePressEvent(event);
}

void GameWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(!isPressed) return;

    setMouseTracking(true);
    //qDebug()<<"move";
    //event->accept();


    QPointF moveDir = event->pos() - mPlayer.getCenterPos();
    qreal _x = moveDir.x();
    qreal _y = moveDir.y();
    _x = QString::number(_x,'f',2).toDouble();
    _y = QString::number(_y,'f',2).toDouble();
    qreal _r = qSqrt(qPow(_x,2) + qPow(_y,2));
    if(_r == 0) return;
    //保留两位小数
    _r = QString::number(_r,'f',2).toDouble();
    qreal dx = _x/_r;
    qreal dy = _y/_r;
    dx = QString::number(dx,'f',2).toDouble();
    dy = QString::number(dy,'f',2).toDouble();
    playerBulletDir = QPointF(dx,dy);

    QWidget::mouseMoveEvent(event);
}

void GameWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(!isRunning) return;
    //qDebug()<<"goodbye";
    isPressed = 0;
    playerShootTimer->stop();
    QWidget::mouseReleaseEvent(event);
}

void GameWidget::enemySummon(int _HP, int _Attack, qreal _Speed, int _exp, int _No)
{
    EnemyBase *Enemy = nullptr;
    switch(_No)
    {
    case 1:
    {
        Enemy = new enemyInsect(GameWidget::widget->getPlayer(),_HP,_Attack,_Speed,_exp);
        break;
    }
    case 2:
    {
        Enemy = new enemyChimera(GameWidget::widget->getPlayer(),_HP,_Attack,_Speed,_exp);
        break;
    }
    case 3:
    {
        Enemy = new enemyBig(GameWidget::widget->getPlayer(),_HP,_Attack,_Speed,_exp);
        break;
    }
    case 4:
    {
        Enemy = new enemyBubble(GameWidget::widget->getPlayer(),_HP,_Attack,_Speed,_exp);
        break;
    }
    case 5:
    {
        Enemy = new enemyBoss(GameWidget::widget->getPlayer(),_HP,_Attack,_Speed,_exp);
        break;
    }
    }
    //生成随机位置
    QPointF tpos(0,0);
    do
    {
        QPointF _pos(QRandomGenerator::global()->bounded(-50,950),QRandomGenerator::global()->bounded(100,750));
        tpos = _pos + QPointF(Enemy->pixmap().width()*Enemy->scale()/2,Enemy->pixmap().height()*Enemy->scale()/2);

    }while(abs((tpos - mPlayer.getCenterPos()).x()) < 200 && abs((tpos - mPlayer.getCenterPos()).y()) < 200);
    //若与玩家过近 重新生成位置

    if(_No == 5)
    {
        Enemy->setPos(0,100);
    }
    else Enemy->setPos(tpos);
    Enemy->setZValue(0.9);
    //auto x = QRandomGenerator::global()->bounded(0,10);

    //绑定怪物死亡与经验球生成
    connect(Enemy,&EnemyBase::isDead,[this,Enemy](){
        auto expBall = new ExpBall(Enemy->getExpDropped(),Enemy->getCenterPos());
        expBall->setZValue(0.8);
        mGameScene.addItem(expBall);
        mExpBallList.append(expBall);
    });
    getGameScene().addItem(Enemy);
    mEnemyList.append(Enemy);

}

QGraphicsScene &GameWidget::getGameScene()
{
    return mGameScene;
}

Player *GameWidget::getPlayer()
{
    return &mPlayer;
}

void GameWidget::setProperties()
{
    QFont font("宋体",11,75);
    //经验条配置
    experienceBar = new QProgressBar(this);
    experienceBar->setMaximum(100);
    experienceBar->setValue(0);
    experienceBar->move(60,100);
    experienceBar->setFixedSize(200,20);
    experienceBar->setFormat(" EXP:0/100");
    experienceBar->setFont(font);
    experienceBar->setOrientation(Qt::Horizontal);

    experienceBar->setStyleSheet(
        "QProgressBar{color:rgb(245,245,245);border-radius: 10px;"
        "background: rgb(0, 0, 0);}"
        "QProgressBar::chunk {border-radius: 10px;"
        "background: rgb(0, 160, 230);}");

    //通过setStyleSheet样式设计进度条样式
    //QProgressBar:进度条背景 设置
    //QProgressBar::chunk 进度条 设置
    //color:字体颜色 ；border-radius:圆角 ；background: 进度条背景颜色 ；

    experienceBar->show();

    //绑定经验值与经验条
    connect(&mPlayer,&Player::getExp,[this](){
        if(mPlayer.getPlayerExp() < 100)
        {
            experienceBar->setValue(mPlayer.getPlayerExp());
            experienceBar->setFormat(" EXP:"+QString::number(mPlayer.getPlayerExp())+"/100");
        }
        else
        {
            mPlayer.LevelBeUp();
            emit mPlayer.LevelUp();//发送升级信号
            isChoosing = 1;

            experienceBar->setValue(mPlayer.getPlayerExp());
            experienceBar->setFormat(" EXP:"+QString::number(mPlayer.getPlayerExp())+"/100");
        }
    });

    //配置等级信息
    LevelLabel = new QLabel(this);
    LevelLabel->move(60,40);
    LevelLabel->setText(" Lv:1");
    LevelLabel->setFixedSize(50,20);
    LevelLabel->setStyleSheet("QLabel{border-radius: 6px;"
                              "background-color: rgb(60, 60, 60);"
                              "color: rgb(255, 255, 255);}");

    LevelLabel->setFont(font);
    connect(&mPlayer,&Player::LevelUp,[this](){
        LevelLabel->setText(" Lv:"+QString::number(mPlayer.getPlayerLevel()));
        //qDebug()<<mPlayer.getPlayerLevel();
        //LevelUPAudioplayer->setSource(QUrl("qrc:/sfx/sounds/effcet_sfx_levelup.ogg"));
        LevelUPAudioplayer->play();
    });

    LevelLabel->show();


    //血量条配置
    HPBar = new QProgressBar(this);
    HPBar->setMaximum(100);
    HPBar->setMaximum(mPlayer.getMaxHP());
    HPBar->setValue(mPlayer.getHP());
    HPBar->move(60,70);
    HPBar->setFixedSize(200,20);
    HPBar->setFormat(" HP:"+QString::number(mPlayer.getHP())+"/"+QString::number(mPlayer.getMaxHP()));
    HPBar->setFont(font);
    HPBar->setOrientation(Qt::Horizontal);

    HPBar->setStyleSheet(
        "QProgressBar{color:rgb(245,245,245);border-radius: 10px;"
        "background: rgb(0, 0, 0);}"
        "QProgressBar::chunk {border-radius: 10px;"
        "background: rgb(240, 40, 40);}");

    HPBar->show();

    //绑定生命值改变与血条变化
    connect(&mPlayer,&Player::LevelUp,[this](){
        resetHPBar();
    });
    connect(this,&GameWidget::isSelected,[this](){
        resetHPBar();
        mPlayer.HPRecoverControl();
    });
    connect(&mPlayer,&Player::isHurt,[this](){
        resetHPBar();
    });


    //细节属性栏配置
    mProperties.setPixmap(QPixmap(":/ui/img/ui/propertiesicons.png"));
    mProperties.setPos(50,310);
    mProperties.setScale(0.7);
    mProperties.setZValue(2);
    mGameScene.addItem(&mProperties);

    HPlabel = new QLabel(this);
    HPRecoverylabel= new QLabel(this);
    HPPlunderlabel= new QLabel(this);
    AttackRatiolabel= new QLabel(this);
    AttackPointlabel= new QLabel(this);
    AttackSpeedlabel= new QLabel(this);
    Defencelabel= new QLabel(this);
    SpeedRatiolabel= new QLabel(this);
    EXPRatiolabel= new QLabel(this);


    //样式表
    QString qssPositive = "QLabel{border-radius: 6px;"
                  "background-color: rgb(60, 60, 60);"
                  "color: rgb(255, 255, 255);}";

    QString qssNegative = "QLabel{border-radius: 6px;"
                          "background-color: rgb(60, 60, 60);"
                          "color: rgb(255, 0, 0);}";

    HPlabel->move(158,325);
    HPlabel->setText("5");
    HPlabel->setFixedSize(30,24);
    HPlabel->setStyleSheet(qssPositive);
    HPlabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    HPlabel->show();

    HPRecoverylabel->move(158,353);
    HPRecoverylabel->setText("0");
    HPRecoverylabel->setFixedSize(30,24);
    HPRecoverylabel->setStyleSheet(qssPositive);
    HPRecoverylabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    HPRecoverylabel->show();

    HPPlunderlabel->move(158,381);
    HPPlunderlabel->setText("0%");
    HPPlunderlabel->setFixedSize(30,24);
    HPPlunderlabel->setStyleSheet(qssPositive);
    HPPlunderlabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    HPPlunderlabel->show();

    AttackRatiolabel->move(158,409);
    AttackRatiolabel->setText("0%");
    AttackRatiolabel->setFixedSize(30,24);
    AttackRatiolabel->setStyleSheet(qssPositive);
    AttackRatiolabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    AttackRatiolabel->show();

    AttackPointlabel->move(158,437);
    AttackPointlabel->setText("1");
    AttackPointlabel->setFixedSize(30,24);
    AttackPointlabel->setStyleSheet(qssPositive);
    AttackPointlabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    AttackPointlabel->show();

    AttackSpeedlabel->move(158,467);
    AttackSpeedlabel->setText("0%");
    AttackSpeedlabel->setFixedSize(30,24);
    AttackSpeedlabel->setStyleSheet(qssPositive);
    AttackSpeedlabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    AttackSpeedlabel->show();

    Defencelabel->move(158,497);
    Defencelabel->setText("0");
    Defencelabel->setFixedSize(30,24);
    Defencelabel->setStyleSheet(qssPositive);
    Defencelabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    Defencelabel->show();

    SpeedRatiolabel->move(158,527);
    SpeedRatiolabel->setText("0%");
    SpeedRatiolabel->setFixedSize(30,24);
    SpeedRatiolabel->setStyleSheet(qssPositive);
    SpeedRatiolabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    SpeedRatiolabel->show();

    EXPRatiolabel->move(158,557);
    EXPRatiolabel->setText("0%");
    EXPRatiolabel->setFixedSize(30,24);
    EXPRatiolabel->setStyleSheet(qssPositive);
    EXPRatiolabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    EXPRatiolabel->show();

    connect(this,&GameWidget::isSelected,[this](){
        isChoosing = 0;
        resetProperties();
    });


}

void GameWidget::resetProperties()
{
    HPlabel->setText(QString::number(mPlayer.getMaxHP()));
    HPRecoverylabel->setText(QString::number(mPlayer.getHPRecovery()));
    HPPlunderlabel->setText(QString::number(mPlayer.getHPPlunder()*100)+"%");
    AttackRatiolabel->setText(QString::number(mPlayer.getAttackRatio()*100)+"%");
    AttackPointlabel->setText(QString::number(mPlayer.getAttackPoint()));
    AttackSpeedlabel->setText(QString::number(mPlayer.getAttackSpeed())+"%");
    Defencelabel->setText(QString::number(mPlayer.getDefence()));
    SpeedRatiolabel->setText(QString::number(mPlayer.getSpeedRatio()*100)+"%");
    EXPRatiolabel->setText(QString::number(mPlayer.getEXPRatio()*100)+"%");
    HPlabel->show();
    HPRecoverylabel->show();
    HPPlunderlabel->show();
    AttackRatiolabel->show();
    AttackPointlabel->show();
    AttackSpeedlabel->show();
    Defencelabel->show();
    SpeedRatiolabel->show();
    EXPRatiolabel->show();
}


void GameWidget::player_enemyCollision()
{
    if(mPlayer.isInvincible) return;//判断无敌
    int enemyNum = mEnemyList.size();
    for(int i=0;i<enemyNum;i++)
    {
        if(mPlayer.collidesWithItem(mEnemyList[i]))
        { 
            mPlayer.getHurt(mEnemyList[i]->getAttackPoint());
            emit mPlayer.isHurt();
            if(mPlayer.getHP() <= 0)//死亡
            {
                emit mPlayer.isDead();
            }
            mPlayer.isInvincible = 1;
            mPlayer.InvincibleTimer->start(GameDefine::InvincibleTime);


            // emit mEnemyList[i]->isDead(); //发出怪物死亡信号
            // mGameScene.removeItem(mEnemyList[i]);
            // if (mEnemyList[i] != nullptr) mEnemyList[i]->deleteLater();
            // mEnemyList.removeOne(mEnemyList[i]);
            // return;
        }
    }
}

void GameWidget::bullet_enemyCollision()
{
    //子弹与敌人碰撞
    int bulletNum = mBulletList.size();
    int enemyNum = mEnemyList.size();
    for(int i=0;i< bulletNum;i++)//遍历所有子弹
    {
        for(int j=0;j<enemyNum;j++)//遍历所有敌人
        {
            if(mBulletList[i]->collidesWithItem(mEnemyList[j]))
            {
                mGameScene.removeItem(mBulletList[i]);

                emit mEnemyList[j]->isHurt(); //发出怪物受伤信号
                mEnemyList[j]->getHurt(mBulletList[i]->getAttackPoint());
                if(mEnemyList[j]->getHP() <= 0 )
                {
                    emit mEnemyList[j]->isDead();//发出怪物死亡信号
                    mGameScene.removeItem(mEnemyList[j]);
                    if (mEnemyList[j] != nullptr) mEnemyList[j]->deleteLater();
                    mEnemyList.removeOne(mEnemyList[j]);
                }

                mPlayer.canPlunder();
                resetHPBar();
                if (mBulletList[i] != nullptr) mBulletList[i]->deleteLater();
                mBulletList.removeOne(mBulletList[i]);

                return;
            }
        }
    }

}

void GameWidget::bullet_playerCollision()
{
    if(mPlayer.isInvincible) return;//判断无敌
    int bulletNum = mEnemyBulletList.size();
    for(int i=0;i<bulletNum;i++)
    {
        if(mEnemyBulletList[i]->collidesWithItem(&mPlayer))
        {
            mPlayer.getHurt(mEnemyBulletList[i]->getAttackPoint());
            emit mPlayer.isHurt();
            if(mPlayer.getHP() <= 0)//死亡
            {
                emit mPlayer.isDead();
            }
            mPlayer.isInvincible = 1;
            mPlayer.InvincibleTimer->start(GameDefine::InvincibleTime);

            if (mEnemyBulletList[i] != nullptr) mEnemyBulletList[i]->deleteLater();
            mEnemyBulletList.removeOne(mEnemyBulletList[i]);

            return;

        }
    }
}

void GameWidget::releaseOutBullet()
{
    for(int i=0;i<mBulletList.size();i++)
    {
        if(mBulletList[i]->getCenterPos().x()>950 || mBulletList[i]->getCenterPos().x()<-50
            || mBulletList[i]->getCenterPos().y()>750 || mBulletList[i]->getCenterPos().y()<-50)
        {
            mGameScene.removeItem(mBulletList[i]);
            if (mBulletList[i] != nullptr) mBulletList[i]->deleteLater();
            mBulletList.removeOne(mBulletList[i]);
            return;
        }
    }
}

void GameWidget::releaseOutEnemyBullet()
{
    for(int i=0;i<mEnemyBulletList.size();i++)
    {
        if(mEnemyBulletList[i]->getCenterPos().x()>1000 || mEnemyBulletList[i]->getCenterPos().x()<-100
            || mEnemyBulletList[i]->getCenterPos().y()>800 || mEnemyBulletList[i]->getCenterPos().y()<-100)
        {
            mGameScene.removeItem(mEnemyBulletList[i]);
            if (mEnemyBulletList[i] != nullptr) mEnemyBulletList[i]->deleteLater();
            mEnemyBulletList.removeOne(mEnemyBulletList[i]);
            return;
        }
    }
}

void GameWidget::getExp()
{
    int expNum = mExpBallList.size();
    for(int i=0;i<expNum;i++)
    {
        if(abs((mExpBallList[i]->getCenterPos()-mPlayer.getCenterPos()).x())<120
            && abs((mExpBallList[i]->getCenterPos()-mPlayer.getCenterPos()).y())<120)
        {
            mExpBallList[i]->expBallMove();
        }
    }
    for(int i=0;i<expNum;i++)
    {
        if(mExpBallList[i]->collidesWithItem(&mPlayer))
        {
            mPlayer.PlayerGetExp(mExpBallList[i]->getVal());
            emit mPlayer.getExp();
            mGameScene.removeItem(mExpBallList[i]);
            if (mExpBallList[i] != nullptr) mExpBallList[i]->deleteLater();
            mExpBallList.removeOne(mExpBallList[i]);
            return;//清除一个后退出 避免“index out of range”
        }
    }
}
