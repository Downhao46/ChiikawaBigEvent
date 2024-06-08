#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include"bullet.h"
#include"player.h"
class playerBullet : public Bullet
{
public:
    playerBullet(Player *_player,QPointF _dir,int _Attack, qreal _speed = 8);
    playerBullet(Player *_player,BulletDir _dir,int _Attack, qreal _speed = 8);
    ~playerBullet()
    {
        //if(pix != nullptr) delete pix;
        //qDebug() << "pix released";
    }


private:
    //QPixmap* pix = new QPixmap(":/icons/img/bulletsample.png");
    Player* mPlayer;


    void PlaySound();

};

#endif // PLAYERBULLET_H
