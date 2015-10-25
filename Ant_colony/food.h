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
    //int getFoodAmount() const;

protected:
    void advance(int phase);

private:
    int id;
    int foodAmount;
    int diameter;

signals:

public slots:
};

#endif // FOOD_H
