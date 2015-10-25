#include "ant.h"
#include "constants.h"

#include <QDebug>
#include <QtMath>

Ant::Ant(int id)
{
    int startX, startY;//, penWidth = 1;
    //radius = 50;
    this->id = id;
    diameter = Constants::ANT_DIAMETER;
    speed = Constants::ANT_SPEED;
    angle = qrand() % 360;

    startX = (qrand() % (Constants::SCENE_RECT_WIDTH - 2*diameter -2) + Constants::SCENE_RECT_X + 1);
    startY = (qrand() % (Constants::SCENE_RECT_HIGH - 2*diameter -2) + Constants::SCENE_RECT_Y + 1);
    qDebug() << startX << " " << startY;

    //not working, don't have scene yet. Set position after added to scene
//    while (!scene()->collidingItems(this).isEmpty())
//    {
//        startX = (qrand() % (Constants::SCENE_RECT_WIDTH - 2*diameter -2) + Constants::SCENE_RECT_X + 1);
//        startY = (qrand() % (Constants::SCENE_RECT_HIGH - 2*diameter -2) + Constants::SCENE_RECT_Y + 1);
//        qDebug() << startX << " " << startY;
//    }

    setPen(QPen(Qt::black));
    setBrush(QBrush(Qt::blue));
    setRect(startX, startY, diameter, diameter);
    //setRect(-radius - penWidth / 2, -radius - penWidth / 2, diameter + penWidth, diameter + penWidth);
}

void Ant::TurnAngleAndMove(int angle)
{
    qreal x, y;
    this->angle += angle;
    x = qCos(qDegreesToRadians(this->angle)) * speed;
    y = qSin(qDegreesToRadians(this->angle)) * speed;
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

    TurnRandomAngleAndMove(Constants::ANT_ANGLE);
    if(scene()->collidingItems(this).isEmpty())
    {
        //no collision
        setBrush(Qt::blue);
    }
    else
    {
//        for (int i = 0, length = scene()->collidingItems(this).length(); i < length; ++i)
//        {
//            qDebug() << "Collision! num: " << i+1 << " pos: " << mapToParent(scene()->collidingItems(this)[i]->pos());
//        }
        //collision!!!!
        setBrush(Qt::red);

        //Set the position
        DoCollision();
    }
}

void Ant::DoCollision()
{
    TurnAngleAndMove(180);
    //QPointF newpoint = mapToParent(-(boundingRect().width()), -(boundingRect().width()));
    //qDebug() << -(boundingRect().width());
//    if(scene()->sceneRect().contains((newpoint)))
//    {
//        setPos(newpoint);
//    }
}
