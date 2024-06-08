#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include<QDebug>

class GameObject : public QGraphicsPixmapItem,public QObject
{

public:
    explicit GameObject(QObject *parent = nullptr);
    ~GameObject();

    QPointF getCenterPos();//获取中心位置

};

#endif // GAMEOBJECT_H
