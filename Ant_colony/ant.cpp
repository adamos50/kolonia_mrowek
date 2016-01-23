#include "ant.h"
#include "constants.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QtMath>

Ant::Ant(int id, Anthill *anthill, QList<Food *> foodList)
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
    this->angle = (this->angle + angle) % 360;
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

QPointF Ant::calculateDifferenceToPos(int x, int y)
{
    return QPointF(x - pos().x() - Constants::ANT_DIAMETER/2,
                   y - pos().y() - Constants::ANT_DIAMETER/2);
}

int Ant::calculateAngleToPos(int x, int y)
{
    QPointF diffPosToAnthill = calculateDifferenceToPos(x, y);
    qreal diffVectorValue = calculateVectorValue(diffPosToAnthill.x(), diffPosToAnthill.y());
    qreal newYVectorValue = abs(diffPosToAnthill.y()) * speed / diffVectorValue;

    int newAngle = qRadiansToDegrees(qAsin(newYVectorValue / speed));
    return newAngle + 180;
}

void Ant::moveToAnthill()
{
    this->angle = calculateAngleToPos(Constants::ANTHILL_X + Constants::ANTHILL_DIAMETER/2,
                                      Constants::ANTHILL_Y + Constants::ANTHILL_DIAMETER/2);
    turnAngleAndMove();
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

void Ant::collectFood(Food* food)
{
    this->foodAmount = food->yieldFood(Constants::ANT_CAPACITY);
    qDebug() << "Ant " << this->id << " collected food.";
}

void Ant::handleFoodCollision()
{
    for (Food* food: foodList)
    {
        if (this->collidesWithItem(food))
        {
            collectFood(food);
        }
    }
}

void Ant::storeFoodToAnthill()
{
    anthill->storeFood(this->foodAmount);
    this->foodAmount = 0;
    qDebug() << "Ant " << this->id << " stored its food to anthill.";
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

    if (isAntFull())
    {
        moveToAnthill();
    }
    else
    {
        turnRandomAngleAndMove(Constants::ANT_ANGLE);
    }

    if(scene()->collidingItems(this).isEmpty())
    {
        //no collision
        setBrush(Qt::blue);
    }
    else
    {
        //collision!!!!

        setBrush(Qt::red);
        turnAngleAndMove(180);

        if (isAntFull())
        {
            if (isCollidingWithAnthill())
            {
                handleAnthillCollision();
            }

            if (isCollidingWithFood())
            {
                QPointF diffFoodPos = calculateDifferenceToPos(foodCollidingItem->x() + foodCollidingItem->getDiameter()/2,
                                                               foodCollidingItem->y() + foodCollidingItem->getDiameter()/2);
                qreal diffVectorValue = calculateVectorValue(diffFoodPos.x(), diffFoodPos.y());

                if (diffVectorValue < this->diameter + foodCollidingItem->getDiameter()/2)
                {

                    int anthillAngle = calculateAngleToPos(Constants::ANTHILL_X + Constants::ANTHILL_DIAMETER/2,
                                                           Constants::ANTHILL_Y + Constants::ANTHILL_DIAMETER/2);
                    int foodAngle = calculateAngleToPos(foodCollidingItem->x() + foodCollidingItem->getDiameter()/2,
                                                        foodCollidingItem->y() + foodCollidingItem->getDiameter()/2);

                    int angleDiff = anthillAngle - foodAngle;


                    qreal leastCentresDistance = qSin(qDegreesToRadians((float)angleDiff)) * diffVectorValue;

                    if (leastCentresDistance <= this->diameter/2 + foodCollidingItem->getDiameter()/2)
                    {

                    }
                }
                turnAngleAndMove();
            }
        }
        else
        {
            if (isCollidingWithFood())
            {
                handleFoodCollision();
            }
        }

        //turnRandomAngleAndMove(-30);
    }
}
