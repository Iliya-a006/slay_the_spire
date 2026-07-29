#include "enemyscene.h"
#include "screensize.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "cultist.h"
#include <QRandomGenerator>
#include "shopscene.h"

EnemyScene::EnemyScene(QWidget *parent)
    : CombatScene(parent)
{
    QPixmap bg(":/prefix1/images/battleBg.png");
    QPixmap scaledBg = bg.scaled(ScreenSize::getSize(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *bgItem = m_scene->addPixmap(scaledBg);
    bgItem->setZValue(-100);
    bgItem->setPos(0, 0);


    QPixmap coin(":/icons/images/coin.png");
    coinItem = m_scene->addPixmap(coin);
    coinItem->setPos(ScreenSize::getWidth()/2 - 38, ScreenSize::getHeigth()/2 -38);
    coinItem->setScale(0.3);
    coinItem->setZValue(101);

    dimmer = new QGraphicsRectItem(m_scene->sceneRect());
    dimmer->setBrush(QColor(0, 0, 0, 180));
    dimmer->setZValue(100);
    m_scene->addItem(dimmer);

    topLabel = new QLabel(this);
    topLabel->setFixedSize(270, 60);
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

    nameLabel = new QLabel("Gold", this);
    nameLabel->setFixedSize(80, 40);
    nameLabel->move(ScreenSize::getWidth()/2 - 30, ScreenSize::getHeigth()/2 + 40);
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
    nextbutton->move(ScreenSize::getWidth() - 150, ScreenSize::getHeigth()/3);
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
            is_end = true;
            nameLabel->hide();
            countLabel->hide();
            coinItem->hide();
            topLabel->setText("Choose a card");
            cardGift();
        }
        else{
            if (m_selectedCard){
                int i;
                for (i=0; i < availableCards.size(); ++i){
                    if (availableCards[i] == m_selectedCard){
                        break;
                    }
                }
                if (i == availableCards.size()) {return;}

                disconnect(availableCards[i], nullptr, this, nullptr);
                m_selectedCard->setOpacity(1.0);
                m_selectedCard = nullptr;

                m_scene->removeItem(availableCards[i]);
                player::instance()->ADD_TO_DRAWPILE(availableCards[i]);
                availableCards.remove(i);

                deleteScene();
                dimmer->hide();
                topLabel->hide();
                nextbutton->hide();
                emit roomExited(true);
            }
        }
    });
}

void EnemyScene::resetRoom()
{
    dimmer->hide();
    topLabel->hide();
    coinItem->hide();
    countLabel->hide();
    nameLabel->hide();
    nextbutton->hide();
    is_end = false;

    this->updateBar();
}

EnemyScene::~EnemyScene()
{
}

void EnemyScene::setupCombat()
{
    Cultist* cultist = new Cultist();
    setEnemy(cultist);
    CombatScene::setupCombat();
}

void EnemyScene::updateUI()
{
    CombatScene::updateUI();
}

void EnemyScene::endTurn()
{
    player* p = player::instance();
    if (!p) return;

    p->END_TURN();
    p->START_TURN();
    updateUI();
}

void EnemyScene::onEndTurnClicked()
{
    endTurn();
}

void EnemyScene::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    if (m_view) {
        m_view->setGeometry(0, 0, width(), height());
    }
    if (m_scene) {
        m_scene->setSceneRect(0, 0, width(), height());
    }

    if (m_endTurnButton) {
        m_endTurnButton->setGeometry(ScreenSize::getWidth() - 150, 30, 120, 40);
    }
}

void EnemyScene::goldGift()
{
    dimmer->show();
    coinItem->show();
    countLabel->show();
    nameLabel->show();
    topLabel->show();
    nextbutton->show();
    NOfGolds = QRandomGenerator::global()->bounded(16) + 15;
    player::instance()->changeGold(NOfGolds);
    //TopBar::instance()->setGold(player::instance()->GETER_GOLD());
    countLabel->setText(QString::number(NOfGolds) + "X");
}

void EnemyScene::cardGift()
{
    showItems();
}

void EnemyScene::showItems()
{
    deleteScene();


    availableCards.resize(3);
    int x, y;
    for (int i=0; i < availableCards.size(); ++i){   // showing cards
        while(!availableCards[i] || availableCards[i]->GETER_RARITY() == BASIC || availableCards[i]->GETER_RARITY() == SPECIAL){
            if (availableCards[i])
                delete availableCards[i];
            availableCards[i] = pickRandomCard();
        }
        m_scene->addItem(availableCards[i]);
        x = ScreenSize::getWidth()/2 - 325 + i*250;
        y = ScreenSize::getHeigth()/2 - 40;
        availableCards[i]->setPos(x, y);
        availableCards[i]->Set_Original_Position(x, y);
        availableCards[i]->setScale(0.5);
        availableCards[i]->Set_Draggable(false);
        availableCards[i]->setAcceptHoverEvents(true);
        connect(availableCards[i], &Card::Card_Clicked, this, &EnemyScene::onCardClicked, Qt::UniqueConnection);
    }
}

Card* EnemyScene::pickRandomCard()
{
    int index = QRandomGenerator::global()->bounded(ShopScene::cardFactories.size());
    return ShopScene::cardFactories[index]();
}

void ShopScene::onCardClicked(Card* card)
{
    if (m_selectedCard == card) {
        return;
    }

    if (m_selectedCard) {
        m_selectedCard->setOpacity(1.0);
    }

    m_selectedCard = card;
    card->setOpacity(0.6);
}

void EnemyScene::deleteScene()
{
    for (auto* card : availableCards) {
        if (card) {
            disconnect(card, nullptr, this, nullptr);
            m_scene->removeItem(card);
            delete card;
        }
    }
    availableCards.clear();
}






