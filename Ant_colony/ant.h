#ifndef ANT_H
#define ANT_H

#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <anthill.h>
#include <food.h>

class Ant : public QGraphicsEllipseItem
{
public:
    Ant(int id,Anthill* anthill, QList<Food *> foodList);
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
    QPointF calculateDifferenceToPos(int x, int y);
    int calculateAngleToPos(int x, int y);
    void moveToAnthill();
    bool isCollidingWithAnthill();
    bool isCollidingWithFood();
    void collectFood(Food* food);
    void handleFoodCollision();
    void storeFoodToAnthill();
    void handleAnthillCollision();
    bool isAntFull();

signals:

public slots:
};

#endif // ANT_H
