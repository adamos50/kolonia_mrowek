#include "anthill.h"
#include "constants.h"

#include <QDebug>

Anthill::Anthill()
{
    foodAmount = 0;
    diameter = Constants::ANTHILL_DIAMETER;

    setPen(QPen(Qt::black));
    setBrush(QBrush(Qt::darkMagenta));
    setRect(0, 0, diameter, diameter);
    setPos(Constants::ANTHILL_X, Constants::ANTHILL_Y);
}

void Anthill::storeFood(int foodAmount)
{
    this-> foodAmount += foodAmount;
    qDebug() << "Food stored in anthill. Actual food amount: " << this-> foodAmount;
}

