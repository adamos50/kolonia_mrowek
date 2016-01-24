#ifndef ANT_H
#define ANT_H

#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QObject>
#include <anthill.h>
#include <food.h>

class Ant : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Ant(int id,Anthill* anthill, QList<Food *> foodList,QObject *parent = 0);
    void setNewPositionIfSceneCollision();

protected:
    void advance(int phase);

private:
    int id;
    int diameter;
    int angle;
    qreal speed;
    int foodAmount;
    Anthill *anthill;
    QList<Food *> foodList;
    Food * foodCollidingItem;

    void turnAngleAndMove(int angle = 0);
    void turnRandomAngleAndMove(int angle);
    qreal calculateVectorValue(qreal x, qreal y);
    QPointF calculateDifferenceToPos(QPointF position);
    int calculateAngleToPos(QPointF position);
    void moveToAnthill();
    void makeAMove();
    bool isCollidingWithAnthill();
    bool isCollidingWithFood();
    void collectFood();
    void handleFoodCollision();
    void storeFoodToAnthill();
    void handleAnthillCollision();
    bool isAntFull();

signals:

public slots:
};

#endif // ANT_H
