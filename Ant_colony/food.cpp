#include "food.h"
#include "constants.h"

#include <QGraphicsScene>
#include <QDebug>

Food::Food(int id)
{
    int startX, startY;

    this->id = id;
    foodAmount = Constants::FOOD_AMOUNT;
    diameter = Constants::FOOD_DIAMETER;

    startX = (qrand() % (Constants::SCENE_RECT_WIDTH - 2*diameter -2) + Constants::SCENE_RECT_X + 1);
    startY = (qrand() % (Constants::SCENE_RECT_HIGH - 2*diameter -2) + Constants::SCENE_RECT_Y + 1);
    qDebug() << "Food start position set.  pos: " << startX << " " << startY;

    setPen(QPen(Qt::black));
    setBrush(QBrush(Qt::darkGreen));
    setRect(0, 0, diameter, diameter);
    setPos(startX, startY);
}

void Food::setNewPositionIfSceneCollision()
{
    while (!scene()->collidingItems(this).isEmpty())
    {
        int startX = (qrand() % (Constants::SCENE_RECT_WIDTH - 2*diameter -2) + Constants::SCENE_RECT_X + 1);
        int startY = (qrand() % (Constants::SCENE_RECT_HIGH - 2*diameter -2) + Constants::SCENE_RECT_Y + 1);
        setPos(startX, startY);
        qDebug() << "Collision! New food position set. pos: " << startX << " " << startY;
    }
}

//int Food::getFoodAmount() const
//{
//    return foodAmount;
//}

void Food::advance(int phase)
{
    if(!phase) return;

    if(scene()->collidingItems(this).isEmpty())
    {
        //no collision
        setBrush(Qt::darkGreen);
    }
    else
    {
        //collision!!!!
        setBrush(Qt::red);
    }
}
