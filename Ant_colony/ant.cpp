#include "ant.h"
#include "constants.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QtMath>

Ant::Ant(int id, Anthill *anthill, QList<Food *> foodList, QObject *parent) : QObject(parent)
{
    int startX, startY;

    this->id = id;
    diameter = Constants::ANT_DIAMETER;
    speed = Constants::ANT_SPEED;
    angle = qrand() % 360;
    foodAmount = 0;
    this->anthill = anthill;
    this->foodList = foodList;

    startX = (qrand() % (Constants::SCENE_RECT_WIDTH - 2*diameter -2) + Constants::SCENE_RECT_X + 1);
    startY = (qrand() % (Constants::SCENE_RECT_HIGH - 2*diameter -2) + Constants::SCENE_RECT_Y + 1);
    qDebug() << "Ant start position set. ant.id: " << this->id << " pos: " << startX << " " << startY;

    setPen(QPen(Qt::black));
    setBrush(QBrush(Qt::blue));
    setRect(0, 0, diameter, diameter);
    setPos(startX, startY);
}

void Ant::setNewPositionIfSceneCollision()
{
    while (!scene()->collidingItems(this).isEmpty())
    {
        int startX = (qrand() % (Constants::SCENE_RECT_WIDTH - 2*diameter -2) + Constants::SCENE_RECT_X + 1);
        int startY = (qrand() % (Constants::SCENE_RECT_HIGH - 2*diameter -2) + Constants::SCENE_RECT_Y + 1);
        setPos(startX, startY);
        qDebug() << "Collision! New ant position set. ant.id: " << id << " pos: " << startX << " " << startY;
    }
}

void Ant::turnAngleAndMove(int angle)
{
    qreal x, y;
    this->angle = ((this->angle + angle) + 360) % 360;
    x = qCos(qDegreesToRadians((float)this->angle)) * speed;
    y = qSin(qDegreesToRadians((float)this->angle)) * speed;
    setPos(mapToParent(x,y));
}

void Ant::turnRandomAngleAndMove(int angle)
{
    int randomAngle = 0;
    //angle E [-angle, angle]
    if (angle != 0)
    {
        randomAngle = qrand() % (2*abs(angle)) - abs(angle);
    }

    if (angle < 0)
    {
        randomAngle += 180;
    }
    turnAngleAndMove(randomAngle);
}

qreal Ant::calculateVectorValue(qreal x, qreal y)
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

QPointF Ant::calculateDifferenceToPos(QPointF position)
{
    return QPointF(pos().x() + this->diameter/2 - position.x(),
                   pos().y() + this->diameter/2 - position.y());
}

int Ant::calculateAngleToPos(QPointF position)
{
    QPointF diffPosition = calculateDifferenceToPos(position);
    qreal diffVectorValue = calculateVectorValue(diffPosition.x(), diffPosition.y());

    int newAngle = qRadiansToDegrees(qAsin(abs(diffPosition.y()) / diffVectorValue));

    if (diffPosition.y() < 0)
    {
        return 180 - newAngle;
    }
    if (diffPosition.x() < 0)
    {
        return 360 - newAngle;
    }
    return 180 + newAngle;
}

void Ant::moveToAnthill()
{
    this->angle = calculateAngleToPos(QPointF(anthill->x(),
                                              anthill->y()));
    turnAngleAndMove();
}

void Ant::makeAMove()
{
    if (isAntFull())
    {
        moveToAnthill();
        setBrush(Qt::red);
    }
    else
    {
        turnRandomAngleAndMove(Constants::ANT_ANGLE);
        setBrush(Qt::blue);
    }
}

bool Ant::isCollidingWithAnthill()
{
    return this->collidesWithItem(anthill);
}

bool Ant::isCollidingWithFood()
{
    for (Food* food: foodList)
    {
        if (this->collidesWithItem(food))
        {
            foodCollidingItem = food;
            return true;
        }
    }
    return false;
}

void Ant::collectFood()
{
    QMutex mutex;
    mutex.lock();
    this->foodAmount = foodCollidingItem->yieldFood(Constants::ANT_CAPACITY);
//    if (this->foodAmount > 0)
//    {
//        qDebug() << "Ant " << this->id << " collected food.";
//    }
    mutex.unlock();
}

void Ant::handleFoodCollision()
{
    collectFood();
}

void Ant::storeFoodToAnthill()
{
    QMutex mutex;
    mutex.lock();
    anthill->storeFood(this->foodAmount);
    this->foodAmount = 0;
    //qDebug() << "Ant " << this->id << " stored its food to anthill.";
    mutex.unlock();
}

void Ant::handleAnthillCollision()
{
    storeFoodToAnthill();
}

bool Ant::isAntFull()
{
    return foodAmount >= Constants::ANT_CAPACITY;
}

void Ant::advance(int phase)
{
    if(!phase) return;

    makeAMove();

    if(scene()->collidingItems(this).isEmpty())
    {
        //no collision
        //setBrush(Qt::blue);
    }
    else
    {
        //collision!!!!

        if (isAntFull())
        {
            if (isCollidingWithAnthill())
            {
                handleAnthillCollision();
                turnAngleAndMove(180);
            }
            else if (isCollidingWithFood())
            {
                QPointF anthillPos = QPointF(anthill->x(),
                                             anthill->y());
                QPointF foodPos = QPointF(foodCollidingItem->x() + foodCollidingItem->getDiameter()/2,
                                          foodCollidingItem->y() + foodCollidingItem->getDiameter()/2);

                int anthillAngle = calculateAngleToPos(anthillPos);
                int foodAngle = calculateAngleToPos(foodPos);

                //qDebug() << "Anthill angle: " << anthillAngle << ". Food angle: " << foodAngle;

                int angleDiff = anthillAngle - foodAngle;

                turnAngleAndMove(180);
                this->angle = foodAngle;

                if (angleDiff < 0)
                {
                    turnAngleAndMove(-90);
                    //qDebug() << "Turn left ant " << this->id;
                }
                else
                {
                    turnAngleAndMove(90);
                    //qDebug() << "Turn right ant " << this->id;
                }
            }
            else
            {
                turnRandomAngleAndMove(-20);
                turnRandomAngleAndMove(20);
            }
        }
        else
        {
            if (isCollidingWithFood())
            {
                handleFoodCollision();
            }
            turnAngleAndMove(180);
        }

        //setBrush(Qt::red);
    }
}
