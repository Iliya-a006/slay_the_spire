#include "map1.h"
#include "ui_map1.h"
#include <QVBoxLayout>
#include "screensize.h"

Map1::Map1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Map1)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene(this);
    m_view  = new QGraphicsView(m_scene, this);
    m_scene->setSceneRect(0, 0, ScreenSize::getWidth(), ScreenSize::getHeigth());
    m_view->setGeometry(0, 0, width(), height());
    //m_view->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_view);
    setLayout(layout);
    //:/prefix1/images/paperBg.png

    QPixmap bg(":/prefix1/images/paperBg.png");
    QPixmap scaledBg = bg.scaled(ScreenSize::getSize(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *bgItem = m_scene->addPixmap(scaledBg);
    bgItem->setZValue(-100);
    bgItem->setPos(0, 0);

}



Map1::~Map1()
{
    delete ui;
}
