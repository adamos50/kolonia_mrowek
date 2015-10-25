#include "anthill.h"
#include "constants.h"

Anthill::Anthill()
{
    foodAmount = Constants::ANTHILL_AMOUNT;
    diameter = Constants::ANTHILL_DIAMETER;

    setPen(QPen(Qt::black));
    setBrush(QBrush(Qt::darkMagenta));
    setRect(0, 0, diameter, diameter);
    setPos(Constants::ANTHILL_X, Constants::ANTHILL_Y);
}

