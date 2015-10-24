#ifndef ANT_H
#define ANT_H

#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>

class Ant : public QGraphicsEllipseItem
{
public:
    Ant();

protected:
    void advance(int phase);

private:
    qreal radius;
    qreal diameter;
    qreal angle;
    qreal speed;
    void TurnAngleAndMove(int angle);
    void TurnRandomAngleAndMove(int angle);
    void DoCollision();

signals:

public slots:
};

#endif // ANT_H
