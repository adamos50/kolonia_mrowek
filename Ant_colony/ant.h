#ifndef ANT_H
#define ANT_H

#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>

class Ant : public QGraphicsEllipseItem
{
public:
    Ant(int id);
    void setNewPositionIfSceneCollision();

protected:
    void advance(int phase);

private:
    int id;
    int diameter;
    qreal angle;
    qreal speed;

    void turnAngleAndMove(int angle);
    void turnRandomAngleAndMove(int angle);
    qreal calculateVectorValue(qreal x, qreal y);
    QPointF calculatePositionToAnthill(qreal diffX, qreal diffY);
    void moveToAnthill();

signals:

public slots:
};

#endif // ANT_H
