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
    return QPointF(position.x() - pos().x() - this->diameter/2,
                   position.y() - pos().y() - this->diameter/2);
}

int Ant::calculateAngleToPos(QPointF position)
{
    QPointF diffPosition = calculateDifferenceToPos(position);
    qreal diffVectorValue = calculateVectorValue(diffPosition.x(), diffPosition.y());

    int newAngle = qRadiansToDegrees(qAsin(abs(diffPosition.y()) / diffVectorValue));
    //qDebug() << "Angle from: (" << pos().x() + this->diameter/2 << " " << pos().y() + this->diameter/2 << ") to (" << position.x() << " " << position.y() << ") is " << newAngle + 180;
    //qDebug() << abs(diffPosition.y()) << " " << diffVectorValue << " " << abs(diffPosition.y()) / diffVectorValue << " " << qAsin(abs(diffPosition.y()) / diffVectorValue);
    return newAngle + 180;
}

void Ant::moveToAnthill()
{
    this->angle = calculateAngleToPos(QPointF(anthill->x() + anthill->getDiameter()/2,
                                              anthill->y() + anthill->getDiameter()/2));
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

void Ant::collectFood()
{
    this->foodAmount = foodCollidingItem->yieldFood(Constants::ANT_CAPACITY);
    qDebug() << "Ant " << this->id << " collected food.";
}

void Ant::handleFoodCollision()
{
    for (Food* food: foodList)
    {
        collectFood();
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

        if (isAntFull())
        {
            if (isCollidingWithAnthill())
            {
                handleAnthillCollision();
                turnAngleAndMove(180);
            }

            if (isCollidingWithFood())
            {
                QPointF anthillPos = QPointF(anthill->x() + anthill->getDiameter()/2,
                                             anthill->y() + anthill->getDiameter()/2);
                QPointF foodPos = QPointF(foodCollidingItem->x() + foodCollidingItem->getDiameter()/2,
                                                      foodCollidingItem->y() + foodCollidingItem->getDiameter()/2);

                int anthillAngle = calculateAngleToPos(anthillPos);
                int foodAngle = calculateAngleToPos(foodPos);

                qDebug() << "Anthill angle: " << anthillAngle << ". Food angle: " << foodAngle;

                int angleDiff = (anthillAngle + 360) % 360 - (foodAngle + 360) % 360;

                turnAngleAndMove(180);
                this->angle = foodAngle;

                if (angleDiff < 0)
                {
                    turnAngleAndMove(-90);
                    qDebug() << "Turn left ant " << this->id;
                }
                else
                {
                    turnAngleAndMove(90);
                    qDebug() << "Turn right ant " << this->id;
                }
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

        setBrush(Qt::red);
        //turnRandomAngleAndMove(-30);
    }
}
