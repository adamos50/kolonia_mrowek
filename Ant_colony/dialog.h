#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
//#include <QtGui>
#include <QGraphicsScene>

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
    void addAntsToScene();
    void setTimerToScene();
};

#endif // DIALOG_H
