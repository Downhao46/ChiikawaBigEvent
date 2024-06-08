#include "gameobject.h"

GameObject::GameObject(QObject *parent)
    :QObject(parent)
{}

GameObject::~GameObject()
{
    //qDebug()<<"gameobject deleted";
}


QPointF GameObject::getCenterPos()
{
    return QPointF(pos().x()+(pixmap().width()*scale()/2),pos().y()+(pixmap().height()*scale()/2));
}
