#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include<QKeyEvent>
#include<QMouseEvent>
#include<QList>
#include<QProgressBar>
#include<QLabel>
#include<QCursor>
#include<QApplication>
#include "gamedefine.h"
#include"player.h"
#include"mybutton.h"
#include"myselectivebutton.h"
#include"bullet.h"
#include"enemybullet.h"
#include"enemyinsect.h"
#include"enemychimera.h"
#include"enemybig.h"
#include"enemybubble.h"
#include"enemyboss.h"
#include"expball.h"
#include<QLCDNumber>
#include<mygraphicsview.h>
#include<QMediaPlayer>
#include<QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui {
class GameWidget;
}
QT_END_NAMESPACE

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    GameWidget(QWidget *parent = nullptr);
    ~GameWidget();

    void Init_Start();
    void Init_Game();
    void restartGame();
    void setTimer();
    void startTimer();
    void stopTimer();
    void GameWin();
    void GameOver();

    bool isRunning = 0;//游戏是否进行中
    bool isChoosing = 0;//是否在选择物品
    bool isStopped = 0;//是否按暂停
    bool isPressed = 0;//鼠标是否按住

    //背景音乐
    QMediaPlayer *BGMplayer = nullptr;
    QAudioOutput *BGMOutput = nullptr;

    //胜利音乐
    QMediaPlayer *WinBGMplayer = nullptr;
    QAudioOutput *WinBGMOutput = nullptr;

    //按钮音效
    QMediaPlayer *ButtonAudioplayer = nullptr;
    QAudioOutput *ButtonAudioOutput = nullptr;

    //升级音效
    QMediaPlayer *LevelUPAudioplayer = nullptr;
    QAudioOutput *LevelUPAudioOutput = nullptr;

    //选择按钮
    mySelectiveButton* optBtn1 = nullptr;
    mySelectiveButton* optBtn2 = nullptr;
    mySelectiveButton* optBtn3 = nullptr;
    int opt1 = 0,opt2 = 0,opt3 = 0;

    void resetHPBar();//重置血条

    QLCDNumber* getGameTime(){return gameClock;}


    void playerMove();

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    QPointF playerBulletDir = QPointF(1,0);

    //生成怪物
    void enemySummon(int _HP, int _Attack, qreal _Speed,int _exp, int _No);

    void player_enemyCollision();//玩家与敌人碰撞检测
    void bullet_enemyCollision();//子弹碰撞检测
    void bullet_playerCollision();//玩家与子弹碰撞
    void releaseOutBullet();//清除出界子弹
    void releaseOutEnemyBullet();
    void getExp();//玩家获取经验

    QGraphicsScene &getGameScene();
    Player* getPlayer();

    static GameWidget* widget;


    QList<Bullet*> mBulletList;//玩家子弹列表
    QList<enemyBullet*> mEnemyBulletList;//怪物子弹列表
    //QList<int> mBulletDirList;//子弹方向
    QList<EnemyBase*> mEnemyList;//怪物列表
    QList<ExpBall*> mExpBallList;//经验球列表

signals:
    void isSelected();//完成选择

private:
    Ui::GameWidget *ui;



    myGraphicsView mGameView; //视图
    QGraphicsScene mStartScene;//开始场景
    QGraphicsScene mGameScene;//游戏场景
    QGraphicsScene mWinScene;//胜利场景
    QGraphicsScene mOverScene;//结束场景

    Player mPlayer;

    myButton* startBtn = nullptr;//开始按钮
    myButton* exitBtn = nullptr;//退出按钮
    myButton* detailBtn = nullptr;
    myButton* backBtn = nullptr;//返回主页
    myButton* restartBtn = nullptr;//再玩一次
    myButton* continueBtn = nullptr;//继续游戏
    GameObject* winText = nullptr;
    GameObject* loseText = nullptr;

    int beginTimes = 0;//开始次数


    myButton* pauseBTN;
    GameObject* grayBackground = nullptr;
    //倒计时
    QLCDNumber* gameClock;
    QTimer* standardTimer;
    //左上角信息
    QProgressBar* experienceBar;
    QProgressBar* HPBar;
    QLabel* LevelLabel;

    //属性栏
    QGraphicsPixmapItem mProperties;
    QLabel* HPlabel;
    QLabel* HPRecoverylabel;
    QLabel* HPPlunderlabel;
    QLabel* AttackRatiolabel;
    QLabel* AttackPointlabel;
    QLabel* AttackSpeedlabel;
    QLabel* Defencelabel;
    QLabel* SpeedRatiolabel;
    QLabel* EXPRatiolabel;

    void setProperties();
    void resetProperties();//重置属性

    //定时器
    QTimer* playerMoveTimer;
    QTimer* playerUpdateTimer;//角色动画
    QTimer* playerShootTimer;
    QTimer* bulletMoveTimer;

    QTimer* BGMTimer;

    QTimer* enemyMoveTimer;//怪物移动

    QList<int> mKeyList;


};
#endif // GAMEWIDGET_H
