#ifndef ANT_H
#define ANT_H

#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Ant : public QGraphicsEllipseItem
{
public:
    Ant(int id);
    void setNewPositionIfSceneCollision();

protected:
    void advance(int phase);

private:
    int id;
    qreal radius;
    int diameter;
    qreal angle;
    qreal speed;
    void TurnAngleAndMove(int angle);
    void TurnRandomAngleAndMove(int angle);

signals:

public slots:
};

#endif // ANT_H
