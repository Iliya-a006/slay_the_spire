#include "campscene.h"
#include <qgraphicsitem.h>
#include <qgraphicsview.h>
#include "player.h"
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
    recallLabel = new QLabel("Lift", this);

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

    titleLabel->move(restButton->x() - 58,
                     restButton->y() - 60);
    restLabel->move(restButton->x() + 32,
                    restButton->y() + 80);
    smithLabel->move(smithButton->x() + 32,
                     smithButton->y() + 80);
    recallLabel->move(recallButton->x() + 32,
                      recallButton->y() + 80);


    leaveLabel = new QLabel(this);
    leaveButton = new QPushButton("Leave", this);
    leaveButton->setFixedSize(100, 40);
    leaveLabel->setStyleSheet("background-color: #FDFBF5;"
                              "color: #2E8B57;"
                              "font-size: 26px;"
                              "font-weight: bold;"
                              "font-family: 'Segoe Print';"
                              "border: 2px solid #2E8B57;"
                              "border-radius: 10px;"
                              "padding: 10px;");
    leaveButton->setStyleSheet("QPushButton {"
                               "    background-color: #F5E6C8;"
                               "    color: #D2691E;"
                               "    font-size: 18px;"
                               "    font-weight: bold;"
                               "    border: 1px solid #D2691E;"
                               "    border-radius: 6px;"
                               "    padding: 5px;"
                               "}"
                               "QPushButton:hover {"
                               "    background-color: #EFD9A8;"
                               "}"
                               "QPushButton:pressed {"
                               "    background-color: #E5C68A;"
                               "}");
    leaveButton->move(ScreenSize::getWidth()/2 - 50, ScreenSize::getHeigth()/2 - 50);


    connect(restButton, &QPushButton::clicked, this, [this](){
        hideOptions();
        restOption();
    });
    connect(smithButton, &QPushButton::clicked, this, [this](){
        hideOptions();
        smithOption();
    });
    connect(recallButton, &QPushButton::clicked, this, [this](){
        hideOptions();
        recallOption();
    });
    connect(leaveButton, &QPushButton::clicked, this, [this](){
        emit roomExited(true);
    });

}



void CampScene::resetRoom()
{
    leaveLabel->hide();
    leaveButton->hide();
    restButton->show();
    smithButton->show();
    recallButton->show();
    titleLabel->show();
    restLabel->show();
    smithLabel->show();
    recallLabel->show();

    restButton->setDisabled(false);
    recallButton->setDisabled(true);
    // relic coffee dripper : restButton->setDisabled(true);
    // relic Girya : recallButton->setDisabled(false);


}

void CampScene::restOption()
{
    int heal = player::instance()->GETER_MAXHP()/5;
    player::instance()->INCREASE_HP(heal);

    showLeavePage("Your HP increased by " + QString::number(heal) + "!");
}

void CampScene::smithOption()
{
    // upgrade a card

    showLeavePage(   "upgraded!");
}

void CampScene::recallOption()
{
    // player recieves a permanent strength

    showLeavePage("You recieved a permanent 'strength'!");
}

void CampScene::hideOptions()
{
    restButton->hide();
    smithButton->hide();
    recallButton->hide();
    titleLabel->hide();
    restLabel->hide();
    smithLabel->hide();
    recallLabel->hide();
}

void CampScene::showLeavePage(QString text)
{
    leaveLabel->show();
    leaveButton->show();
    leaveLabel->setText(text);
    leaveLabel->adjustSize();
    leaveLabel->move(ScreenSize::getWidth()/2 - leaveLabel->width()/2, ScreenSize::getHeigth()/2 - 150);

}

CampScene::~CampScene()
{

}
