#include "dialog.h"
#include "ui_dialog.h"
#include "ant.h"
#include "constants.h"

#include <QThread>
#include <QDebug>

void Dialog::addRectangularBoundaryLinesToScene(Qt::GlobalColor color)
{
    QPen myPen = QPen(color);

    QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    QLineF BottomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

    scene->addLine(TopLine, myPen);
    scene->addLine(LeftLine, myPen);
    scene->addLine(RightLine, myPen);
    scene->addLine(BottomLine, myPen);
}

void Dialog::addGraphicsViewToUi()
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(Constants::SCENE_RECT_X, Constants::SCENE_RECT_Y,
                        Constants::SCENE_RECT_WIDTH, Constants::SCENE_RECT_HIGH);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

Anthill* Dialog::addAnthillToScene()
{
    Anthill *anthill = new Anthill();
    scene->addItem(anthill);
    return anthill;
}

QList<Food *> Dialog::addFoodToScene()
{
    QList<Food *> foodList;
    for(int i = 0; i < Constants::FOOD_COUNT; ++i)
    {
        Food *food = new Food(i+1);
        foodList.push_back(food);
        scene->addItem(food);
        food->setNewPositionIfSceneCollision();
    }
    return foodList;
}

void Dialog::addAntsToScene(Anthill* anthill, QList<Food *> foodList)
{
    for(int i = 0; i < Constants::ANTS_COUNT; ++i)
    {
        Ant *ant = new Ant(i+1, anthill, foodList, this);
        scene->addItem(ant);
        ant->setNewPositionIfSceneCollision();

        QThread* antThread = new QThread(this);
        ant->moveToThread(antThread);
        antThread->start();
    }
}

void Dialog::setTimerToScene()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(Constants::TIMER_STEP_MS);
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    addGraphicsViewToUi();
    addRectangularBoundaryLinesToScene(Qt::red);

    Anthill* anthill =  addAnthillToScene();
    QList<Food *> foodList = addFoodToScene();

    addAntsToScene(anthill, foodList);
    setTimerToScene();
}

Dialog::~Dialog()
{
    delete ui;
}
