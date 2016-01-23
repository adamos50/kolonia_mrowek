#include "graphicalvertex.h"

GraphicalVertex::GraphicalVertex()
{
    diameter = 15;

    setPen(QPen(Qt::black));
    setBrush(QBrush(Qt::lightGray));
    setRect(0, 0, diameter, diameter);
    setPos(Constants::ANTHILL_X, Constants::ANTHILL_Y);
}

