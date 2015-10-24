#include "dialog.h"
#include "ui_dialog.h"
#include "ant.h"
#include "constants.h"

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

void Dialog::addAntsToScene()
{
    for(int i = 0; i < Constants::ANTS_COUNT; ++i)
    {
        Ant *ant = new Ant();
        scene->addItem(ant);
        qDebug() << ant->rect();
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
    addAntsToScene();
    setTimerToScene();
}

Dialog::~Dialog()
{
    delete ui;
}
