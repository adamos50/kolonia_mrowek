#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QGraphicsScene>
#include "anthill.h"
#include "food.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    QTimer *timer;

    void addRectangularBoundaryLinesToScene(Qt::GlobalColor color);
    void addGraphicsViewToUi();
    Anthill *addAnthillToScene();
    QList<Food *> addFoodToScene();
    void addAntsToScene(Anthill* anthill, QList<Food *> foodList);
    void setTimerToScene();
};

#endif // DIALOG_H
