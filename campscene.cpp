#include "campscene.h"
#include <qgraphicsitem.h>
#include <qgraphicsview.h>
#include "screensize.h"

CampScene::CampScene(QWidget *parent)
    : RoomScene(parent)
{
    m_scene = new QGraphicsScene(this);
    m_view  = new QGraphicsView(m_scene, this);
    m_scene->setSceneRect(0, 0, ScreenSize::getWidth(), ScreenSize::getHeigth());
    m_view->setGeometry(0, 0, ScreenSize::getWidth(), ScreenSize::getHeigth());
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap bg(":/prefix1/images/restBg.png");
    QPixmap scaledBg = bg.scaled(ScreenSize::getSize(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *bgItem = m_scene->addPixmap(scaledBg);
    bgItem->setZValue(-100);
    bgItem->setPos(0, 0);


    restButton = new QPushButton(this);
    smithButton = new QPushButton(this);
    recallButton = new QPushButton(this);

    restButton->setFixedSize(115, 73);
    smithButton->setFixedSize(115, 73);
    recallButton->setFixedSize(115, 73);

    restButton->setStyleSheet("QPushButton {"
                              "    background-image: url(:/icons/images/rest.jpg);"
                              "    background-repeat: no-repeat;"
                              "    border: none;"
                              "}");
    smithButton->setStyleSheet("QPushButton {"
                               "    background-image: url(:/icons/images/smith.jpg);"
                               "    background-repeat: no-repeat;"
                               "    border: none;"
                               "}");
    recallButton->setStyleSheet("QPushButton {"
                               "    background-image: url(:/icons/images/recall.jpg);"
                               "    background-repeat: no-repeat;"
                               "    border: none;"
                               "}");

    restButton->move(ScreenSize::getWidth()/2 - ScreenSize::getWidth()/10 - 57,
                     ScreenSize::getHeigth()/2 - ScreenSize::getHeigth()/4.6);
    smithButton->move(ScreenSize::getWidth()/2 + ScreenSize::getWidth()/10 - 57,
                      ScreenSize::getHeigth()/2 - ScreenSize::getHeigth()/4.6);
    recallButton->move(ScreenSize::getWidth()/2 - 57,
                      ScreenSize::getHeigth()/2);

    titleLabel = new QLabel("Time for a break...", this);
    restLabel = new QLabel("Rest", this);
    smithLabel = new QLabel("Smith", this);
    recallLabel = new QLabel("Recall", this);

    titleLabel->setFixedSize(250, 40);
    restLabel->setFixedSize(70, 30);
    smithLabel->setFixedSize(70, 30);
    recallLabel->setFixedSize(70, 30);

    titleLabel->setStyleSheet("background-color: #F5E6C8;"
                              "color: black;"
                              "font-size: 24px;"
                              "font-weight: bold;"
                              "font-family: 'Segoe Print';"
                              "border-radius: 6px;"
                              "padding: 5px;");
    restLabel->setStyleSheet("color: #D2691E;"
                             "font-size: 18px;"
                             "font-weight: bold;"
                             "padding: 5px;");
    smithLabel->setStyleSheet("color: #D2691E;"
                             "font-size: 18px;"
                             "font-weight: bold;"
                             "padding: 5px;");
    recallLabel->setStyleSheet("color: #D2691E;"
                             "font-size: 18px;"
                             "font-weight: bold;"
                             "padding: 5px;");

    titleLabel->move(ScreenSize::getWidth()/2 - ScreenSize::getWidth()/10 - 115,
                     ScreenSize::getHeigth()/2 - ScreenSize::getHeigth()/4.6 - 60);
    restLabel->move(ScreenSize::getWidth()/2 - ScreenSize::getWidth()/10 - 25,
                    ScreenSize::getHeigth()/2 - ScreenSize::getHeigth()/4.6 + 80);
    smithLabel->move(ScreenSize::getWidth()/2 + ScreenSize::getWidth()/10 - 25,
                     ScreenSize::getHeigth()/2 - ScreenSize::getHeigth()/4.6 + 80);
    recallLabel->move(ScreenSize::getWidth()/2 - 25,
                      ScreenSize::getHeigth()/2 + 80);



}

void CampScene::resetRoom()
{

}

CampScene::~CampScene()
{

}
