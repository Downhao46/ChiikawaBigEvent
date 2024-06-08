#include "myselectivebutton.h"
#include"gamewidget.h"

QStringList mySelectiveButton::itemDescriptions =
{
    "※睡衣套装\n1.生命值 +3\n2.防御 +2\n3.移速 -5%\n*抵御一次致命伤",
    "※吉伊的包包\n1.经验加成 +10%\n2.生命恢复 +2",
    "※美味蛋糕\n1.攻击力 +2\n2.伤害率 +5%",
    "※奇怪的法杖\n1.子弹数 +1\n2.生命值 -5\n3.防御 -3",
    "※大叔的肉夹馍\n1.攻击力 +1\n2.生命值 +2",
    "※郎拉面\n1.攻击力 +2\n2.生命值 +2\n3.防御 +2",
    "※乌龙茶\n1.攻击速度 +10%\n2.生命恢复 +2\n3.移速 +3%",
    "※柠檬水\n1.移速 +5%\n2.生命窃取 +5%",
    "※柠檬酸\n1.攻击力 +2\n2.防御 -1\n3.生命窃取 +5%",
    "※牛排\n1.生命值 +3\n2.生命恢复 +3\n3.伤害率 +5%",
    "※师傅的大剑\n1.攻击力 +5\n2.伤害率 +10%\n3.攻击速度 +10%",
    "※学习资料\n1.经验加成 +15%\n2.伤害率 +5%",
    "※指虎\n1.攻击力 +3\n2.攻击速度 +15%\n3.防御 -2",
    "※小八的相机\n1.防御 +5\n2.经验加成 -10%",
    "※吉伊的玩偶\n1.生命值 +4\n2.生命恢复 +2",
    "※五级除草证\n1.经验加成 +10%\n2.生命值 +1\n3.防御 +1",
    "※三级除草证\n1.经验加成 +20%\n2.攻击速度 +10%",
    "※寿喜烧大礼包\n1.伤害率 +10%\n2.生命值 +5\n3.移速 -5%",
    "※吉他\n1.攻击速度 +15%\n2.防御 +2",
    "※星星魔棒\n1.额外子弹 +2\n2.伤害率 -10%\n3.攻击速度 -20%\n*额外子弹上限为4",
    "※超级可口酸奶\n1.攻击速度 +5%\n2.生命值 +2\n3.生命恢复 +3",
    "※草莓冰淇淋\n1.伤害率 +10%\n2.生命值 +2\n3.移速 +5%",
    "※魔手\n1.伤害率 -50%\n2.攻击力 -10\n3.生命窃取 +10%\n*伤害绑定敌人HP",
    "※皇冠\n1.击退系数 +1\n2.防御 +3\n3.经验加成 -20%"
};
mySelectiveButton::mySelectiveButton(QWidget *parent)
    : QToolButton{parent}
{}

mySelectiveButton::~mySelectiveButton()
{
    //delete label;
}

mySelectiveButton::mySelectiveButton(int _itemID, QWidget *parent)
    :QToolButton{parent}
{

    itemID = _itemID;
    this->setFixedSize(100,100);

    QString address = ":/item/img/items/itemicon";
    address += QString::number(itemID);
    address += ".png";
    this->setIcon(QIcon(address));
    this->setIconSize(QSize(100,100));
    this->setAutoRaise(true);
    //this->setStyleSheet("QToolButton{border-radius: 6px;}");

}

void mySelectiveButton::enterEvent(QEnterEvent *event)
{
    if(label == nullptr)
    {
        label = new QLabel(GameWidget::widget);
        label->move(this->pos() + QPoint(0,120));
        label->setFixedSize(100,80);
        //label->setText(QString::number(itemID));//物品信息
        label->setText(itemDescriptions.at(itemID));
        label->setStyleSheet("QLabel{border-radius: 6px;"
                                  "background-color: rgb(60, 60, 60);"
                                  "color: rgb(250, 250, 250);}");
    }
    label->show();
}

void mySelectiveButton::leaveEvent(QEvent *event)
{
    label->hide();

}
