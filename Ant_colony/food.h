#ifndef FOOD_H
#define FOOD_H

#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>

class Food : public QGraphicsEllipseItem
{
public:
    Food(int id);
    void setNewPositionIfSceneCollision();
    int yieldFood(int foodAmount);
    int getDiameter() const;

protected:
    //void advance(int phase);

private:
    int id;
    int foodAmount;
    int diameter;

signals:

public slots:
};

#endif // FOOD_H
