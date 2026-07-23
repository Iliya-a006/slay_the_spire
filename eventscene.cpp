#include "eventscene.h"
#include <qboxlayout.h>
#include <qgraphicsitem.h>
#include <qgraphicsview.h>
#include "augmenterevent.h"
#include "facetraderevent.h"
#include "goldenidolevent.h"
#include "goldenshrineevent.h"
#include "joustevent.h"
#include "labevent.h"
#include "ominousforgeevent.h"
#include "screensize.h"
#include <QRandomGenerator>
#include "player.h"
#include "serpantevent.h"

EventScene::EventScene(QWidget *parent)
    : RoomScene(parent)
{
    m_scene = new QGraphicsScene(this);
    m_view  = new QGraphicsView(m_scene, this);
    m_scene->setSceneRect(0, 0, ScreenSize::getWidth(), ScreenSize::getHeigth());
    m_view->setGeometry(0, 0, ScreenSize::getWidth(), ScreenSize::getHeigth());
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap bg(":/prefix1/images/greenBg.png");
    QPixmap scaledBg = bg.scaled(ScreenSize::getSize(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *bgItem = m_scene->addPixmap(scaledBg);
    bgItem->setZValue(-100);
    bgItem->setPos(0, 0);


    frame = new QFrame(this);
    frame->setFixedSize(1000, 500);
    frame->move(ScreenSize::getWidth()/2 - 500, ScreenSize::getHeigth()/2 - 250);
    frame->setFrameShape(QFrame::Box);
    frame->setStyleSheet("QFrame { background-color: black; border-radius: 10px; }");

    pictureLabel = new QLabel(frame);
    nameLabel = new QLabel(frame);
    describtionLabel = new QLabel(frame);
    nameLabel->setStyleSheet(
        "background-color: #F5E6C8;"
        "color: black;"
        "font-size: 20px;"
        "font-weight: bold;"
        "border-radius: 6px;"
        "padding: 5px;"
        );
    describtionLabel->setStyleSheet(labelStyle);
    describtionLabel->setWordWrap(true);
    leaveButton = new QPushButton("Leave", frame);
    leaveButton->move(600, 380);
    leaveButton->setFixedSize(100, 40);
    leaveButton->setStyleSheet(buttonStyle);
    connect(leaveButton, &QPushButton::clicked, this, [this](){
        emit roomExited(true);
    });
}

void EventScene::resetRoom()
{
    if (event)
        delete event;
    for (auto b : buttons)
        delete b;
    buttons.clear();
    leaveButton->hide();
    showEvent();
}

void EventScene::showEvent()
{
    int chance;
    if (player::instance()->getAct() == 1)
        chance = QRandomGenerator::global()->bounded(5);
    else
        chance = QRandomGenerator::global()->bounded(6)+2;

    switch (chance) {
    case 0:
        event = new GoldenIdolEvent();
        break;
    case 1:
        event = new SerpantEvent();
        break;
    case 2:
        event = new LabEvent();
        break;
    case 3:
        event = new OminousForgeEvent();
        break;
    case 4:
        event = new GoldenShrineEvent();
        break;
    case 5:
        event = new FaceTraderEvent();
        break;
    case 6:
        event = new AugmenterEvent();
        break;
    case 7:
        event = new JoustEvent();
        break;
    default:
        break;
    }

    pictureLabel->setFixedSize(500, 500);
    pictureLabel->setAlignment(Qt::AlignCenter);
    pictureLabel->move(0, 0);
    pictureLabel->setPixmap(QPixmap(event->picture));
    QPixmap pic(event->picture);
    qDebug() << "Path:" << event->picture << "isNull:" << pic.isNull();

    nameLabel->move(500, 0);
    nameLabel->setFixedWidth(500);
    nameLabel->setText(event->name);

    describtionLabel->move(530, 40);
    describtionLabel->setFixedSize(440, 300);
    describtionLabel->setText(event->description);

    for (int i=0; i < event->eventOptions.size(); ++i){
        buttons.push_back(new QPushButton(frame));
        buttons[i]->setText(event->eventOptions[i].buttonText);
        buttons[i]->move(600, 380 + (i*40));
        buttons[i]->setFixedSize(buttons[i]->text().length()*20, 35);
        buttons[i]->setStyleSheet(buttonStyle);
        connect(buttons[i], &QPushButton::clicked, this, [this, i](){
            event->eventOptions[i].action();
            goToLeavePage(i);
        });
    }
}

void EventScene::goToLeavePage(int i)
{
    describtionLabel->clear();
    describtionLabel->setText(event->eventOptions[i].description);
    for (auto b : buttons)
        b->hide();
    leaveButton->show();
}

EventScene::~EventScene()
{

}
