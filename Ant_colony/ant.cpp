#include "ant.h"
#include <QtMath>

Ant::Ant()
{
    int startX, startY;
    //qreal penWidth = 1;
    //radius = 50;
    diameter = 20;
    speed = 5;
    angle = qrand() % 360;

    startX = ((qrand() % 200) - 100)*2;
    startY = ((qrand() % 200) - 100)*2;

    setRect(startX, startY, diameter, diameter);
    setPen(QPen(Qt::black));
    setBrush(QBrush(Qt::blue));
    //setRect(-radius - penWidth / 2, -radius - penWidth / 2, diameter + penWidth, diameter + penWidth);
}

void Ant::TurnAngleAndMove(int angle)
{
    qreal x, y;
    x = qCos(qDegreesToRadians(this->angle)) * speed;
    y = qSin(qDegreesToRadians(this->angle)) * speed;
    this->angle += angle;
    setPos(mapToParent(x,y));
}

void Ant::TurnRandomAngleAndMove(int angle)
{
    //angle E [-angle, angle]
    angle = qrand() % (2*angle) - angle;
    TurnAngleAndMove(angle);
}

void Ant::advance(int phase)
{
    if(!phase) return;

    QPointF location = this->pos();
    if(scene()->collidingItems(this).isEmpty())
    {
        //no collision
        setBrush(Qt::blue);
    }
    else
    {
        //collision!!!!
        setBrush(Qt::red);

        //Set the position
        //DoCollision();
    }
    TurnRandomAngleAndMove(30);
}

void Ant::DoCollision()
{
    setRotation(rotation() + (180 + (qrand() % 20) - 10));
    QPointF newpoint = mapToParent(-(boundingRect().width()), -(boundingRect().width()));
    qDebug() << -(boundingRect().width());
    if(scene()->sceneRect().contains((newpoint)))
    {
        setPos(newpoint);
    }
}
