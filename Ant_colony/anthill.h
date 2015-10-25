#ifndef ANTHILL_H
#define ANTHILL_H

#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>

class Anthill : public QGraphicsEllipseItem
{
public:
    Anthill();

private:
    int foodAmount;
    int diameter;

signals:

public slots:
};

#endif // ANTHILL_H
