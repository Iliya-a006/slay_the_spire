#include "treasurescene.h"
#include <qgraphicsitem.h>
#include <qgraphicsview.h>
#include "player.h"
#include "screensize.h"
#include "chest.h"
#include "topbar.h"
#include <QRandomGenerator>

TreasureScene::TreasureScene(QWidget *parent)
    : RoomScene(parent)
{
    m_scene = new QGraphicsScene(this);
    m_view  = new QGraphicsView(m_scene, this);
    m_scene->setSceneRect(0, 0, ScreenSize::getWidth(), ScreenSize::getHeigth());
    m_view->setGeometry(0, 0, ScreenSize::getWidth(), ScreenSize::getHeigth());
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap bg(":/prefix1/images/battleBg.png");
    QPixmap scaledBg = bg.scaled(ScreenSize::getSize(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *bgItem = m_scene->addPixmap(scaledBg);
    bgItem->setZValue(-100);
    bgItem->setPos(0, 0);


    QPixmap avatarPix(":/avatar/images/Ironclad.png");
    QGraphicsPixmapItem* avatarItem = m_scene->addPixmap(avatarPix);
    avatarItem->setPos(50, (ScreenSize::getHeigth() / 2) - 130);
    avatarItem->setScale(0.8);

    chest = new Chest;
    chest->setPos(ScreenSize::getWidth()*2/3, (ScreenSize::getHeigth() / 2) - 50);
    chest->setScale(0.5);
    m_scene->addItem(chest);

    connect(chest, &Chest::ChestClicked, this, &TreasureScene::onChestClicked);


    QPixmap coin(":/icons/images/coin.png");
    coinItem = m_scene->addPixmap(coin);
    coinItem->setPos(ScreenSize::getWidth()/2 - 38, ScreenSize::getHeigth()/2 -38);
    coinItem->setScale(0.3);
    coinItem->setZValue(2);

    dimmer = new QGraphicsRectItem(m_scene->sceneRect());
    dimmer->setBrush(QColor(0, 0, 0, 180));
    dimmer->setZValue(1);
    m_scene->addItem(dimmer);

    topLabel = new QLabel("YOU RECIEVED!", this);
    topLabel->setFixedSize(250, 60);
    topLabel->move(ScreenSize::getWidth()/2 - topLabel->width()/2, ScreenSize::getHeigth()/2 - topLabel->height() - 40);
    topLabel->setStyleSheet("QLabel {"
                            "   background: transparent;"
                            "   color: #FFD700;"
                            "   font-family: 'Vazirmatn';"
                            "   font-size: 28px;"
                            "   font-weight: 900;"
                            "   border: none;"
                            "}");

    countLabel = new QLabel(this);
    countLabel->setFixedSize(60, 40);
    countLabel->move(ScreenSize::getWidth()/2 - 80, ScreenSize::getHeigth()/2 - 20);
    countLabel->setStyleSheet("QLabel {"
                              "   background: transparent;"
                              "   color: #FFD700;"
                              "   font-family: 'Vazirmatn';"
                              "   font-size: 20px;"
                              "   font-weight: 900;"
                              "   border: none;"
                              "}");

    nameLabel = new QLabel(this);
    nameLabel->setStyleSheet("QLabel {"
                             "   background: transparent;"
                             "   color: #FFD700;"
                             "   font-family: 'Vazirmatn';"
                             "   font-size: 20px;"
                             "   font-weight: 900;"
                             "   border: none;"
                             "}");


    nextbutton = new QPushButton("Next", this);
    nextbutton->setFixedSize(80, 40);
    nextbutton->move(ScreenSize::getWidth() - 150, ScreenSize::getHeigth()*2/3);
    nextbutton->setStyleSheet(R"(
    QPushButton {
        background-color: rgba(10, 35, 40, 180);
        border: 2px solid #2ec4b6;
        border-radius: 8px;
        color: #a8e6e0;
        font-size: 18px;
        font-weight: bold;
        padding: 10px;
    }
    QPushButton:hover {
        background-color: rgba(46, 196, 182, 220);
        color: white;
    }
    QPushButton:pressed {
        background-color: rgba(20, 120, 110, 255);
    }
    )");

    connect(nextbutton, &QPushButton::clicked, this, [this](){
        if (!is_end){
            // hide relic icon
            goldGift();
        }
        else{
            emit roomExited(true);
        }
    });
}

void TreasureScene::resetRoom()
{
    dimmer->hide();
    topLabel->hide();
    coinItem->hide();
    countLabel->hide();
    nameLabel->hide();
    nextbutton->hide();
    recieved = false;
    is_end = false;

    this->updateBar();
}

void TreasureScene::onChestClicked()
{
    if (recieved)
        return;
    dimmer->show();
    topLabel->show();
    nextbutton->show();
    nameLabel->show();
    recieved = true;

    relicGift();
}

void TreasureScene::goldGift()
{
    is_end = true;
    // hide relic icon
    coinItem->show();
    countLabel->show();
    NOfGolds = QRandomGenerator::global()->bounded(31) + 30;
    player::instance()->changeGold(NOfGolds);
    TopBar::instance()->setGold(player::instance()->GETER_GOLD());

    countLabel->setText(QString::number(NOfGolds) + "X");
    QString name = "Gold";
    nameLabel->setText(name);
    nameLabel->setFixedSize(80, 40);
    nameLabel->move(ScreenSize::getWidth()/2 - name.size()/2*15, ScreenSize::getHeigth()/2 + 40);
}

void TreasureScene::relicGift()
{
    // select a random relic
    countLabel->hide();
    // nameLabel->show();
    // Qstring name = relic name
    // nameLabel->setText( name );
    // naemLabel->setFixedSize(    );
    // nameLabel->move(ScreenSize::getWidth()/2 - name.size()/2*15, ScreenSize::getHeigth()/2 + 40);
}

TreasureScene::~TreasureScene()
{

}
