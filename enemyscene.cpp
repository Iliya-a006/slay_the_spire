#include "enemyscene.h"
#include "screensize.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>

EnemyScene::EnemyScene(QWidget *parent)
    : RoomScene(parent),
    m_currentEnemy(nullptr),
    m_enemyItem(nullptr),
    m_enemyHPText(nullptr),
    m_enemyIntentText(nullptr)
{
    m_scene = new QGraphicsScene(this);
    m_view  = new QGraphicsView(m_scene, this);
    m_scene->setSceneRect(0, 0, ScreenSize::getWidth(), ScreenSize::getHeigth());
    m_view->setGeometry(0, 0, ScreenSize::getWidth(), ScreenSize::getHeigth());
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setStyleSheet("background: transparent; border: none;");
    m_view->setAttribute(Qt::WA_TranslucentBackground);
    m_view->viewport()->setStyleSheet("background: transparent;");

    QPixmap bg(":/prefix1/images/battleBg.png");
    QPixmap scaledBg = bg.scaled(ScreenSize::getSize(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *bgItem = m_scene->addPixmap(scaledBg);
    bgItem->setZValue(-100);
    bgItem->setPos(0, 0);

    m_playerAvatar = nullptr;
    m_hpBarBg = nullptr;
    m_hpBar = nullptr;
    m_hpText = nullptr;
    m_energyText = nullptr;
    m_endTurnButton = nullptr;


}

EnemyScene::~EnemyScene()
{
    clearCards();
    if (m_playerAvatar) {
        m_scene->removeItem(m_playerAvatar);
        delete m_playerAvatar;
        m_playerAvatar = nullptr;
    }
    if (m_hpBarBg) {
        m_scene->removeItem(m_hpBarBg);
        delete m_hpBarBg;
        m_hpBarBg = nullptr;
    }
    if (m_hpBar) {
        m_scene->removeItem(m_hpBar);
        delete m_hpBar;
        m_hpBar = nullptr;
    }
    if (m_hpText) {
        m_scene->removeItem(m_hpText);
        delete m_hpText;
        m_hpText = nullptr;
    }
    if (m_energyText) {
        m_scene->removeItem(m_energyText);
        delete m_energyText;
        m_energyText = nullptr;
    }
    if (m_endTurnButton) {
        delete m_endTurnButton;
        m_endTurnButton = nullptr;
    }
    if (m_enemyItem) {
        m_scene->removeItem(m_enemyItem);
        delete m_enemyItem;
        m_enemyItem = nullptr;
    }
    if (m_enemyHPText) {
        m_scene->removeItem(m_enemyHPText);
        delete m_enemyHPText;
        m_enemyHPText = nullptr;
    }
    if (m_enemyIntentText) {
        m_scene->removeItem(m_enemyIntentText);
        delete m_enemyIntentText;
        m_enemyIntentText = nullptr;
    }
}

void EnemyScene::resetRoom()
{

}

void EnemyScene::setupCombat()
{
    connectPlayerSignals();
    setupPlayerAvatar();
    setupHPBar();
    setupEnergyLabel();
    setupEndTurnButton();
    setupEnemy();
    setupPlayerCards();
    updateUI();
}

void EnemyScene::setEnemy(Enemy* enemy)
{
    m_currentEnemy = enemy;
}

void EnemyScene::connectPlayerSignals()
{
    player* p = player::instance();
    if (!p) return;

    connect(p, &player::hpChanged, this, [=](int newHP, int maxHP) {
        updateHPBar();
    });

    connect(p, &player::energyChanged, this, [=](int newEnergy) {
        updateEnergyLabel();
    });

    connect(p, &player::handUpdated, this, [=]() {
        clearCards();
        setupPlayerCards();
    });
}

void EnemyScene::setupPlayerAvatar()
{
    player* p = player::instance();
    if (!p) return;

    if (m_playerAvatar) {
        m_scene->removeItem(m_playerAvatar);
        delete m_playerAvatar;
        m_playerAvatar = nullptr;
    }

    m_playerAvatar = new QGraphicsPixmapItem();
    m_playerAvatar->setPixmap(p->pixmap());
    m_playerAvatar->setScale(0.8);

    int avatarX = 50;
    int avatarY = (ScreenSize::getHeigth() / 2) - 100;
    m_playerAvatar->setPos(avatarX, avatarY);
    m_scene->addItem(m_playerAvatar);
}

void EnemyScene::setupHPBar()
{
    player* p = player::instance();
    if (!p) return;

    int avatarX = 50;
    int avatarY = (ScreenSize::getHeigth() / 2) - 100;
    int avatarHeight = 80;

    m_hpBarBg = new QGraphicsRectItem();
    m_hpBarBg->setRect(avatarX, avatarY + avatarHeight + 10, 100, 15);
    m_hpBarBg->setBrush(Qt::black);
    m_hpBarBg->setPen(QPen(Qt::gray, 1));
    m_scene->addItem(m_hpBarBg);

    m_hpBar = new QGraphicsRectItem();
    m_hpBar->setRect(avatarX + 2, avatarY + avatarHeight + 12, 96, 11);
    m_hpBar->setBrush(Qt::green);
    m_hpBar->setPen(Qt::NoPen);
    m_scene->addItem(m_hpBar);

    m_hpText = new QGraphicsTextItem();
    m_hpText->setPos(avatarX + 20, avatarY + avatarHeight + 8);
    QFont font("Vazirmatn", 10, QFont::Bold);
    m_hpText->setFont(font);
    m_hpText->setDefaultTextColor(Qt::white);
    m_scene->addItem(m_hpText);

    updateHPBar();
}

void EnemyScene::updateHPBar()
{
    player* p = player::instance();
    if (!p) return;
    if (!m_hpBar || !m_hpText) return;

    int currentHP = p->GETER_HP();
    int maxHP = p->GETER_MAXHP();

    float percent = (float)currentHP / maxHP;
    int barWidth = 96 * percent;

    QRectF rect = m_hpBar->rect();
    rect.setWidth(barWidth);
    m_hpBar->setRect(rect);

    if (percent > 0.5) {
        m_hpBar->setBrush(Qt::green);
    } else if (percent > 0.25) {
        m_hpBar->setBrush(Qt::yellow);
    } else {
        m_hpBar->setBrush(Qt::red);
    }

    m_hpText->setPlainText(QString("%1/%2").arg(currentHP).arg(maxHP));
}

void EnemyScene::setupEnergyLabel()
{
    player* p = player::instance();
    if (!p) return;

    int avatarX = 50;
    int avatarY = (ScreenSize::getHeigth() / 2) - 100;
    int avatarHeight = 80;

    m_energyText = new QGraphicsTextItem();
    m_energyText->setPos(avatarX + 110, avatarY + avatarHeight + 8);
    QFont font("Vazirmatn", 12, QFont::Bold);
    m_energyText->setFont(font);
    m_energyText->setDefaultTextColor(Qt::yellow);
    m_scene->addItem(m_energyText);

    updateEnergyLabel();
}

void EnemyScene::updateEnergyLabel()
{
    player* p = player::instance();
    if (!p) return;
    if (!m_energyText) return;

    int energy = p->GETER_ENERGY();
    m_energyText->setPlainText(QString("⚡ %1").arg(energy));
}

void EnemyScene::setupEndTurnButton()
{
    m_endTurnButton = new QPushButton("End Turn", this);
    m_endTurnButton->setGeometry(ScreenSize::getWidth() - 150, 30, 120, 40);

    m_endTurnButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #8B4513;"
        "   color: white;"
        "   border: 2px solid white;"
        "   border-radius: 10px;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   font-family: 'Vazirmatn';"
        "}"
        "QPushButton:hover {"
        "   background-color: #A0522D;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #654321;"
        "}"
        );

    connect(m_endTurnButton, &QPushButton::clicked, this, &EnemyScene::onEndTurnClicked);
}

void EnemyScene::onEndTurnClicked()
{
    endTurn();
}

void EnemyScene::endTurn()
{
    player* p = player::instance();
    if (!p) return;

    p->END_TURN();
    p->START_TURN();

    updateUI();
}

void EnemyScene::setupEnemy()
{
    if (!m_currentEnemy) return;

    if (m_enemyItem) {
        m_scene->removeItem(m_enemyItem);
        delete m_enemyItem;
        m_enemyItem = nullptr;
    }

    m_enemyItem = new QGraphicsPixmapItem();
    m_enemyItem->setPixmap(m_currentEnemy->pixmap());
    m_enemyItem->setScale(0.8);
    m_enemyItem->setPos((ScreenSize::getWidth() / 2) - 50, 80);
    m_scene->addItem(m_enemyItem);

    if (m_enemyHPText) {
        m_scene->removeItem(m_enemyHPText);
        delete m_enemyHPText;
        m_enemyHPText = nullptr;
    }
    m_enemyHPText = new QGraphicsTextItem();
    QFont font("Vazirmatn", 14, QFont::Bold);
    m_enemyHPText->setFont(font);
    m_enemyHPText->setDefaultTextColor(Qt::red);
    m_enemyHPText->setPos((ScreenSize::getWidth() / 2) - 50, 200);
    m_scene->addItem(m_enemyHPText);

    if (m_enemyIntentText) {
        m_scene->removeItem(m_enemyIntentText);
        delete m_enemyIntentText;
        m_enemyIntentText = nullptr;
    }
    m_enemyIntentText = new QGraphicsTextItem();
    QFont intentFont("Vazirmatn", 12, QFont::Bold);
    m_enemyIntentText->setFont(intentFont);
    m_enemyIntentText->setDefaultTextColor(Qt::yellow);
    m_enemyIntentText->setPos((ScreenSize::getWidth() / 2) - 60, 240);
    m_scene->addItem(m_enemyIntentText);

    updateEnemyUI();
}

void EnemyScene::updateEnemyUI()
{
    if (!m_currentEnemy) return;
    if (m_enemyHPText) {
        m_enemyHPText->setPlainText(QString("HP: %1/%2").arg(m_currentEnemy->getHP()).arg(m_currentEnemy->getMaxHP()));
    }
    if (m_enemyIntentText) {
        Intent intent = m_currentEnemy->getNextIntent();
        QString intentText;
        switch (intent.type) {
        case Intent::ATTACK: intentText = "⚔️ Attack: " + QString::number(intent.value); break;
        case Intent::DEFEND: intentText = "🛡️ Defend: " + QString::number(intent.value); break;
        case Intent::BUFF:   intentText = "✨ Buff: " + intent.description; break;
        case Intent::DEBUFF: intentText = "💀 Debuff: " + intent.description; break;
        case Intent::MIXED:  intentText = "⚡ Mixed: " + intent.description; break;
        default: intentText = "❓ Unknown";
        }
        m_enemyIntentText->setPlainText(intentText);
    }
}

void EnemyScene::setupPlayerCards()
{
    player* p = player::instance();
    if (!p) return;

    clearCards();

    QVector<Card*>& hand = p->GETٍER_HAND();
    if (hand.isEmpty()) return;

    int cardWidth = 100;
    int cardHeight = 140;
    int cardSpacing = 20;

    int totalWidth = hand.size() * (cardWidth + cardSpacing) - cardSpacing;
    int startX = (ScreenSize::getWidth() - totalWidth) / 2;
    int yPos = ScreenSize::getHeigth() - cardHeight - 80;

    for (int i = 0; i < hand.size(); ++i) {
        Card* card = hand[i];
        if (!card) continue;

        card->setPos(startX + i * (cardWidth + cardSpacing), yPos);
        card->setScale(0.5);
        card->Set_Original_Position(startX + i * (cardWidth + cardSpacing), yPos);
        card->setAcceptHoverEvents(true);
        card->setFlag(QGraphicsItem::ItemIsSelectable, false);
        card->setFlag(QGraphicsItem::ItemIsMovable, true);

        connect(card, &Card::Card_Dropped_On_Enemy, this, [=](Card* c, Enemy* e) {
            if (c->canPlay(p)) {
                int cost = c->getCurrentCost(p);
                if (p->GETER_ENERGY() >= cost) {
                    QList<Enemy*> enemies;
                    enemies.append(e);
                    c->play(p, enemies);
                    p->SPEND_ENERGY(cost);
                    p->REMOVE_FROM_HAND(c);
                    updateUI();
                }
            }
        });

        connect(card, &Card::Card_Dropped_On_Player, this, [=](Card* c) {
            if (c->canPlay(p)) {
                int cost = c->getCurrentCost(p);
                if (p->GETER_ENERGY() >= cost) {
                    QList<Enemy*> empty;
                    c->play(p, empty);
                    p->SPEND_ENERGY(cost);
                    p->REMOVE_FROM_HAND(c);
                    updateUI();
                }
            }
        });

        m_scene->addItem(card);
        m_cardItems.append(card);
    }
}

void EnemyScene::clearCards()
{
    for (auto item : m_cardItems) {
        m_scene->removeItem(item);
        disconnect(item, nullptr, this, nullptr);
    }
    m_cardItems.clear();
}

void EnemyScene::updateUI()
{
    player* p = player::instance();
    if (p && m_playerAvatar) {
        m_playerAvatar->setPixmap(p->pixmap());
    }

    updateHPBar();
    updateEnergyLabel();
    updateEnemyUI();
    clearCards();
    setupPlayerCards();
}

void EnemyScene::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    m_view->setGeometry(0, 0, width(), height());
    m_scene->setSceneRect(0, 0, width(), height());

    if (m_endTurnButton) {
        m_endTurnButton->setGeometry(ScreenSize::getWidth() - 150, 30, 120, 40);
    }
}