#include "ant.h"
#include "constants.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QtMath>

Ant::Ant(int id)
{
    int startX, startY;

    this->id = id;
    diameter = Constants::ANT_DIAMETER;
    speed = Constants::ANT_SPEED;
    angle = qrand() % 360;

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
    this->angle += angle;
    x = qCos(qDegreesToRadians(this->angle)) * speed;
    y = qSin(qDegreesToRadians(this->angle)) * speed;
    setPos(mapToParent(x,y));
}

void Ant::turnRandomAngleAndMove(int angle)
{
    //angle E [-angle, angle]
    angle = qrand() % (2*angle) - angle;
    turnAngleAndMove(angle);
}

void Ant::goToAnthill()
{

}

void Ant::advance(int phase)
{
    if(!phase) return;

    turnRandomAngleAndMove(Constants::ANT_ANGLE);

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
    }
}
