#include "shopscene.h"
#include <qgraphicsitem.h>
#include <qgraphicsview.h>
#include "screensize.h"
#include "vendor.h"
#include <QRandomGenerator>
#include <qtimer.h>
#include "player.h"

ShopScene::ShopScene(QWidget *parent)
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

    vendor = new Vendor;
    vendor->setPos(ScreenSize::getWidth()/2, ScreenSize::getHeigth() / 4);
    vendor->setScale(0.8);
    m_scene->addItem(vendor);

    connect(vendor, &Vendor::VendorClicked, this, &ShopScene::onVendorClicked);


    shopScene = new QGraphicsScene(this);
    shopView  = new QGraphicsView(shopScene, this);

    shopScene->setBackgroundBrush(QColor(178, 235, 230));
    shopScene->setSceneRect(0, 0, 930, 570);
    shopView->setGeometry(ScreenSize::getWidth()/2 - 465, ScreenSize::getHeigth()/2 - 285, 930, 570);
    shopView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    shopView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    leaveButton = new QPushButton("Leave", this);
    leaveButton->setFixedSize(100, 40);
    leaveButton->move(shopView->x() + shopView->width() + 50, shopView->y());
    leaveButton->setStyleSheet(R"(
    QPushButton {
        background-color: rgba(40, 20, 15, 180);
        border: 2px solid #c97a3d;
        border-radius: 8px;
        color: #f0d78c;
        font-size: 18px;
        font-weight: bold;
        padding: 10px;
    }
    QPushButton:hover {
        background-color: rgba(201, 122, 61, 220);
        color: white;
    }
    QPushButton:pressed {
        background-color: rgba(150, 90, 40, 255);
    }
    )");
    connect(leaveButton, &QPushButton::clicked, this, [this](){
        emit roomExited(true);
    });

    buyButton = new QPushButton("Buy", this);
    buyButton->setFixedSize(60, 50);
    buyButton->move(shopView->x() + shopView->width() + 50, shopView->y() + 60);
    buyButton->setStyleSheet(leaveButton->styleSheet());
    connect(buyButton, &QPushButton::clicked, this, [this](){
        if (m_selectedCard){
            int i, cost;
            for (i=0; i < availableCards.size(); ++i){
                if (availableCards[i] == m_selectedCard){
                    break;
                }
            }
            if (i == availableCards.size()) {return;}
            cost = cardsCost[i]->toPlainText().toInt();
            if (player::instance()->GETER_GOLD() >= cost){
                disconnect(availableCards[i], nullptr, this, nullptr);
                m_selectedCard->setOpacity(1.0);
                m_selectedCard = nullptr;

                shopScene->removeItem(availableCards[i]);
                shopScene->removeItem(cardsCost[i]);
                shopScene->removeItem(cardsCoinItems[i]);
                player::instance()->changeGold(-cost);
                player::instance()->ADD_TO_DRAWPILE(availableCards[i]);
                delete cardsCost[i];
                delete cardsCoinItems[i];
                availableCards.remove(i);
                cardsCost.remove(i);
                cardsCoinItems.remove(i);
            }
            else{
                redLabel->show();
                QTimer::singleShot(3000, this, [this](){
                    redLabel->hide();
                });
            }
        }
    });

    redLabel = new QLabel("You have not enough gold!", this);
    redLabel->setFixedSize(500, 60);
    redLabel->move(ScreenSize::getWidth()/2 - redLabel->width()/2, 100);
    redLabel->setStyleSheet("background-color: #F8D7DA;"
                            "color: #721C24;"
                            "font-size: 24px;"
                            "font-weight: bold;"
                            "font-family: 'Segoe Print';"
                            "border-radius: 6px;"
                            "padding: 5px;"
                            "border: 1px solid #F5C2C7;");
}

void ShopScene::resetRoom()
{
    buyButton->hide();
    redLabel->hide();
    clicked = false;
    m_selectedCard = nullptr;
    showItems();
    shopView->hide();
}

void ShopScene::onVendorClicked()
{
    if (clicked)
        return;
    clicked = true;
    shopView->show();
    buyButton->show();
}

void ShopScene::showItems()
{
    deleteScene();


    availableCards.resize(7);
    int x, y;
    for (int i=0; i < availableCards.size(); ++i){   // showing cards
        while(!availableCards[i] || availableCards[i]->GETER_RARITY() == BASIC || availableCards[i]->GETER_RARITY() == SPECIAL){
            if (availableCards[i])
                delete availableCards[i];
            availableCards[i] = pickRandomCard();
        }
        shopScene->addItem(availableCards[i]);
        x = i%5 * (150 + 30) - 23;
        y = i/5 * (210 + 50) + 26;
        availableCards[i]->setPos(x, y);
        availableCards[i]->Set_Original_Position(x, y);
        availableCards[i]->setScale(0.5);
        availableCards[i]->Set_Draggable(false);
        availableCards[i]->setAcceptHoverEvents(true);
        connect(availableCards[i], &Card::Card_Clicked, this, &ShopScene::onCardClicked, Qt::UniqueConnection);
    }


    QPixmap coin(":/icons/images/coin.png");
    QFont font("Arial", 14, QFont::Bold);
    int cost;
    cardsCost.resize(availableCards.size());
    cardsCoinItems.resize(availableCards.size());
    for (int i=0; i < availableCards.size(); ++i) {   // showing cost
        cost = costCalculation(availableCards[i]);

        cardsCost[i] = new QGraphicsTextItem();
        shopScene->addItem(cardsCost[i]);
        cardsCost[i]->setFont(font);
        cardsCost[i]->setDefaultTextColor(QColor(184, 134, 11));
        cardsCost[i]->setPos(availableCards[i]->x() + 50, availableCards[i]->y() + 230);
        cardsCost[i]->setPlainText(QString::number(cost));

        QGraphicsPixmapItem* coinItem = shopScene->addPixmap(coin);
        coinItem->setPos(cardsCost[i]->x() + 40, cardsCost[i]->y());
        coinItem->setScale(0.1);
        cardsCoinItems[i] = coinItem;
    }


    removal = new CardRemoval();   // showing card removal service
    removal->setPos(750, 310);
    shopScene->addItem(removal);
    connect(removal, &CardRemoval::removalClicked, this, &ShopScene::onRemovalClicked, Qt::UniqueConnection);

    removalText = new QGraphicsTextItem();
    shopScene->addItem(removalText);
    removalText->setFont(font);
    removalText->setDefaultTextColor(QColor(184, 134, 11));
    removalText->setPos(removal->x(), removal->y() + 210);
    removalText->setPlainText(QString::number(50 + player::instance()->getRemovalUsed()*25));

    QGraphicsPixmapItem* coinItem = shopScene->addPixmap(coin);
    coinItem->setPos(removalText->x() + 40, removalText->y());
    coinItem->setScale(0.1);
    //removalCoinItem = coinItem;
}

Card* ShopScene::pickRandomCard()
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

    //upgradeButton->setDisabled(false);
}

int ShopScene::costCalculation(Card* card)
{
    Card_Rarity r = card->GETER_RARITY();

    switch (r) {
    case BASIC:
    case SPECIAL:
        return 0;
        break;

    case COMMON:
    case UNCOMMON:
        return 100 + QRandomGenerator::global()->bounded(51);
        break;

    case RARE:
        return 280 + QRandomGenerator::global()->bounded(21);
        break;

    default:
        return 0;
        break;
    }
}

void ShopScene::onRemovalClicked()
{

}

void ShopScene::deleteScene()
{
    for (auto* card : availableCards) {
        if (card) {
            disconnect(card, nullptr, this, nullptr);
            shopScene->removeItem(card);
            delete card;
        }
    }
    availableCards.clear();

    for (auto* item : cardsCost) {
        if (item) {
            shopScene->removeItem(item);
            delete item;
        }
    }
    cardsCost.clear();

    for (auto* item : cardsCoinItems) {
        if (item) {
            shopScene->removeItem(item);
            delete item;
        }
    }
    cardsCoinItems.clear();

    if (removal) {
        disconnect(removal, nullptr, this, nullptr);
        shopScene->removeItem(removal);
        delete removal;
        removal = nullptr;
    }

    if (removalText) {
        shopScene->removeItem(removalText);
        delete removalText;
        removalText = nullptr;
    }

    if (removalCoinItem) {
        shopScene->removeItem(removalCoinItem);
        delete removalCoinItem;
        removalCoinItem = nullptr;
    }
}

ShopScene::~ShopScene()
{

}



QVector<std::function<Card*()>> ShopScene::cardFactories = {
    []() -> Card* { return new Strike(); },
    []() -> Card* { return new TwinStrike(); },
    []() -> Card* { return new BloodForBlood(); },
    []() -> Card* { return new Hemokinesis(); },
    []() -> Card* { return new Carnage(); },
    []() -> Card* { return new Whirlwind(); },
    []() -> Card* { return new Bludgeon(); },
    []() -> Card* { return new Immolate(); },
    []() -> Card* { return new Reaper(); },
    []() -> Card* { return new Feed(); },

    []() -> Card* { return new Defend(); },
    []() -> Card* { return new Exhume(); },
    []() -> Card* { return new LimitBreak(); },
    []() -> Card* { return new Offering(); },
    []() -> Card* { return new Impervious(); },
    []() -> Card* { return new DualWield(); },
    []() -> Card* { return new Entrench(); },
    []() -> Card* { return new Warcry(); },
    []() -> Card* { return new TrueGrit(); },
    []() -> Card* { return new ShrugItOff(); },

    []() -> Card* { return new Inflame(); },
    []() -> Card* { return new class Metallicize(); },
    []() -> Card* { return new class DemonForm(); },
    []() -> Card* { return new class Brutality(); },
    []() -> Card* { return new class FeelNoPain(); },
    []() -> Card* { return new class Barricade(); },
    []() -> Card* { return new class DarkEmbrace(); },
    []() -> Card* { return new class Berserk(); },
};






