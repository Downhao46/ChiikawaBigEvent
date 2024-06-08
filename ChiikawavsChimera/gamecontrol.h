#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include<QObject>
#include<QDebug>

class GameControl : public QObject
{
    GameControl();
    static GameControl* instance;
public:
    static GameControl* Instance()
    {
        if(instance == nullptr)
        {
            return instance = new GameControl();
        }
        return instance;
    }

    ~GameControl()
    {
        //qDebug()<<"gamecontrol released";
    }

    void EnemySummonControl(int _time);

private:
    int GameTime;

};

#endif // GAMECONTROL_H
