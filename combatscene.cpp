#include "combatscene.h"
#include "screensize.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include "map1.h"
#include "topbar.h"

CombatScene::CombatScene(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("background: transparent;");

    m_scene = new QGraphicsScene(this);
    m_view = new QGraphicsView(m_scene, this);

    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setStyleSheet("background: transparent; border: none;");
    m_view->setAttribute(Qt::WA_TranslucentBackground);
    m_view->viewport()->setStyleSheet("background: transparent;");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_view);
    setLayout(layout);

    m_view->setGeometry(0, 0, width(), height());
    m_scene->setSceneRect(0, 0, ScreenSize::getWidth(), ScreenSize::getHeigth());
    m_scene->setBackgroundBrush(Qt::transparent);

    m_playerAvatar = nullptr;
    m_currentEnemy = nullptr;
    m_enemyItem = nullptr;
    m_enemyHPText = nullptr;
    m_enemyIntentText = nullptr;
    m_enemyHpBarBg = nullptr;
    m_enemyHpBar = nullptr;
    m_hpBarBg = nullptr;
    m_hpBar = nullptr;
    m_hpText = nullptr;
    m_energyText = nullptr;
    m_endTurnButton = nullptr;


    connect(this, &CombatScene::roomExited, Map1::instance(), &Map1::onRoomExited);
}

void CombatScene::resetRoom()
{

}

CombatScene::~CombatScene()
{
    clearCards();
    deleteEnemy();

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
    if (m_enemyHpBarBg) {
        m_scene->removeItem(m_enemyHpBarBg);
        delete m_enemyHpBarBg;
        m_enemyHpBarBg = nullptr;
    }
    if (m_enemyHpBar) {
        m_scene->removeItem(m_enemyHpBar);
        delete m_enemyHpBar;
        m_enemyHpBar = nullptr;
    }
}

void CombatScene::setEnemy(Enemy* enemy)
{
    deleteEnemy();
    m_currentEnemy = enemy;
    if (enemy) {
        connect(enemy, &Enemy::enemyDied, this, &CombatScene::onEnemyDied);
    }
}

void CombatScene::setupCombat()
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

void CombatScene::connectPlayerSignals()
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

void CombatScene::setupPlayerAvatar()
{
    player* p = player::instance();
    if (!p) return;

    if (m_playerAvatar) {
        m_scene->removeItem(m_playerAvatar);
        delete m_playerAvatar;
        m_playerAvatar = nullptr;
    }

    const int ITEM_SIZE = 180;
    const int MARGIN = 50;

    m_playerAvatar = new QGraphicsPixmapItem();

    QPixmap avatarPixmap = p->pixmap();
    if (!avatarPixmap.isNull()) {
        QPixmap scaledPixmap = avatarPixmap.scaled(ITEM_SIZE, ITEM_SIZE,
                                                   Qt::KeepAspectRatio,
                                                   Qt::SmoothTransformation);
        m_playerAvatar->setPixmap(scaledPixmap);
    } else {
        m_playerAvatar->setPixmap(avatarPixmap);
    }

    int avatarX = MARGIN;
    int avatarY = (ScreenSize::getHeigth() / 2) - (ITEM_SIZE / 2);
    m_playerAvatar->setPos(avatarX, avatarY);
    m_scene->addItem(m_playerAvatar);
}

void CombatScene::setupHPBar()
{
    player* p = player::instance();
    if (!p) return;

    const int ITEM_SIZE = 180;
    const int MARGIN = 50;

    int avatarX = MARGIN;
    int avatarY = (ScreenSize::getHeigth() / 2) - (ITEM_SIZE / 2);


    m_hpBarBg = new QGraphicsRectItem();
    m_hpBarBg->setRect(avatarX, avatarY + ITEM_SIZE + 10, 180, 20);
    m_hpBarBg->setBrush(Qt::black);
    m_hpBarBg->setPen(QPen(Qt::gray, 1));
    m_scene->addItem(m_hpBarBg);


    m_hpBar = new QGraphicsRectItem();
    m_hpBar->setRect(avatarX + 3, avatarY + ITEM_SIZE + 13, 174, 14);
    m_hpBar->setBrush(Qt::green);
    m_hpBar->setPen(Qt::NoPen);
    m_scene->addItem(m_hpBar);


    m_hpText = new QGraphicsTextItem();
    m_hpText->setPos(avatarX + 40, avatarY + ITEM_SIZE + 8);
    QFont font("Vazirmatn", 12, QFont::Bold);
    m_hpText->setFont(font);
    m_hpText->setDefaultTextColor(Qt::white);
    m_scene->addItem(m_hpText);

    updateHPBar();
}

void CombatScene::updateHPBar()
{
    player* p = player::instance();
    if (!p) return;
    if (!m_hpBar || !m_hpText) return;

    int currentHP = p->GETER_HP();
    int maxHP = p->GETER_MAXHP();

    float percent = (float)currentHP / maxHP;
    int barWidth = 174 * percent;

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

void CombatScene::setupEnergyLabel()
{
    player* p = player::instance();
    if (!p) return;

    const int ITEM_SIZE = 180;
    const int MARGIN = 50;

    int avatarX = MARGIN;
    int avatarY = (ScreenSize::getHeigth() / 2) - (ITEM_SIZE / 2);

    m_energyText = new QGraphicsTextItem();
    m_energyText->setPos(avatarX + ITEM_SIZE + 15, avatarY + ITEM_SIZE + 8);
    QFont font("Vazirmatn", 14, QFont::Bold);
    m_energyText->setFont(font);
    m_energyText->setDefaultTextColor(Qt::yellow);
    m_scene->addItem(m_energyText);

    updateEnergyLabel();
}

void CombatScene::updateEnergyLabel()
{
    player* p = player::instance();
    if (!p) return;
    if (!m_energyText) return;

    int energy = p->GETER_ENERGY();
    m_energyText->setPlainText(QString("⚡ %1").arg(energy));
}

void CombatScene::setupEndTurnButton()
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

    connect(m_endTurnButton, &QPushButton::clicked, this, &CombatScene::onEndTurnClicked);
}

void CombatScene::onEndTurnClicked()
{
    endTurn();
}

void CombatScene::endTurn()
{
    player* p = player::instance();
    if (!p) return;

    p->END_TURN();
    p->START_TURN();

    updateUI();
}

void CombatScene::setupEnemy()
{
    if (!m_currentEnemy) return;

    clearEnemy();

    const int ITEM_SIZE = 180;
    const int MARGIN = 50;

    int avatarX = MARGIN;
    int avatarY = (ScreenSize::getHeigth() / 2) - (ITEM_SIZE / 2);

    int enemyX = ScreenSize::getWidth() - MARGIN - ITEM_SIZE;
    int enemyY = avatarY-30;

    m_enemyItem = new QGraphicsPixmapItem();

    QPixmap enemyPixmap = m_currentEnemy->pixmap();
    if (!enemyPixmap.isNull()) {
        QPixmap scaledPixmap = enemyPixmap.scaled(ITEM_SIZE, ITEM_SIZE,
                                                  Qt::KeepAspectRatio,
                                                  Qt::SmoothTransformation);
        m_enemyItem->setPixmap(scaledPixmap);
    } else {
        QPixmap fallback(ITEM_SIZE, ITEM_SIZE);
        fallback.fill(QColor(200, 50, 50));
        QPainter painter(&fallback);
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 12, QFont::Bold));
        painter.drawText(fallback.rect(), Qt::AlignCenter,
                         m_currentEnemy->getName());
        m_enemyItem->setPixmap(fallback);
    }

    m_enemyItem->setPos(enemyX, enemyY);
    m_scene->addItem(m_enemyItem);


    m_enemyHpBarBg = new QGraphicsRectItem();
    m_enemyHpBarBg->setRect(enemyX, enemyY + ITEM_SIZE + 10, 180, 20);
    m_enemyHpBarBg->setBrush(Qt::black);
    m_enemyHpBarBg->setPen(QPen(Qt::gray, 1));
    m_scene->addItem(m_enemyHpBarBg);


    m_enemyHpBar = new QGraphicsRectItem();
    m_enemyHpBar->setRect(enemyX + 3, enemyY + ITEM_SIZE + 13, 174, 14);
    m_enemyHpBar->setBrush(Qt::red);
    m_enemyHpBar->setPen(Qt::NoPen);
    m_scene->addItem(m_enemyHpBar);


    m_enemyHPText = new QGraphicsTextItem();
    m_enemyHPText->setPos(enemyX + 40, enemyY + ITEM_SIZE + 8);
    QFont font("Vazirmatn", 12, QFont::Bold);
    m_enemyHPText->setFont(font);
    m_enemyHPText->setDefaultTextColor(Qt::white);
    m_scene->addItem(m_enemyHPText);


    m_enemyIntentText = new QGraphicsTextItem();
    QFont intentFont("Vazirmatn", 13, QFont::Bold);
    m_enemyIntentText->setFont(intentFont);
    m_enemyIntentText->setDefaultTextColor(Qt::yellow);
    m_enemyIntentText->setPos(enemyX - 30, enemyY + ITEM_SIZE + 45);
    m_scene->addItem(m_enemyIntentText);

    disconnect(m_currentEnemy, &Enemy::intentChanged, this, nullptr);
    disconnect(m_currentEnemy, &Enemy::hpChanged, this, nullptr);

    connect(m_currentEnemy, &Enemy::intentChanged, this, [=](const Intent& intent) {
        updateEnemyUI();
    });
    connect(m_currentEnemy, &Enemy::hpChanged, this, [=](int newHP, int maxHP) {
        updateEnemyUI();
    });

    m_currentEnemy->getNextIntent();
    updateEnemyUI();
}

void CombatScene::clearEnemy()
{
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
    if (m_enemyHpBarBg) {
        m_scene->removeItem(m_enemyHpBarBg);
        delete m_enemyHpBarBg;
        m_enemyHpBarBg = nullptr;
    }
    if (m_enemyHpBar) {
        m_scene->removeItem(m_enemyHpBar);
        delete m_enemyHpBar;
        m_enemyHpBar = nullptr;
    }
}

void CombatScene::deleteEnemy()
{
    clearEnemy();
    if (m_currentEnemy) {
        delete m_currentEnemy;
        m_currentEnemy = nullptr;
    }
}

void CombatScene::updateEnemyUI()
{
    if (!m_currentEnemy) return;

    int currentHP = m_currentEnemy->getHP();
    int maxHP = m_currentEnemy->getMaxHP();


    if (m_enemyHPText) {
        m_enemyHPText->setPlainText(QString("%1/%2").arg(currentHP).arg(maxHP));
    }


    if (m_enemyHpBar) {
        float percent = (float)currentHP / maxHP;
        int barWidth = 174 * percent;

        QRectF rect = m_enemyHpBar->rect();
        rect.setWidth(barWidth);
        m_enemyHpBar->setRect(rect);

        if (percent > 0.5) {
            m_enemyHpBar->setBrush(Qt::green);
        } else if (percent > 0.25) {
            m_enemyHpBar->setBrush(Qt::yellow);
        } else {
            m_enemyHpBar->setBrush(Qt::red);
        }
    }


    if (m_enemyIntentText) {
        Intent intent = m_currentEnemy->getCurrentIntent();
        QString intentText;
        switch (intent.type) {
        case Intent::ATTACK: intentText = "⚔️ Attack: " + QString::number(intent.value); break;
        case Intent::DEFEND: intentText = "🛡️ Defend: " + QString::number(intent.value); break;
        case Intent::BUFF:   intentText = "✨ Buff"; break;
        case Intent::DEBUFF: intentText = "💀 Debuff"; break;
        case Intent::MIXED:  intentText = "⚡ Mixed"; break;
        default: intentText = "❓ Unknown";
        }
        m_enemyIntentText->setPlainText(intentText);
    }
}

void CombatScene::onEnemyDied(Enemy* enemy)
{
    if (m_currentEnemy == enemy) {
        if (m_enemyHPText) {
            m_enemyHPText->setPlainText("💀");
        }
        if (m_enemyHpBar) {
            m_enemyHpBar->setRect(m_enemyHpBar->rect().x(),
                                  m_enemyHpBar->rect().y(),
                                  0,
                                  m_enemyHpBar->rect().height());
        }
        if (m_enemyIntentText) {
            m_enemyIntentText->setPlainText("💀 Defeated!");
        }
    }
}

void CombatScene::setupPlayerCards()
{
    player* p = player::instance();
    if (!p) return;

    clearCards();

    QVector<Card*>& hand = p->GETER_HAND();
    if (hand.isEmpty()) return;

    int cardWidth = 100;
    int cardHeight = 140;
    int cardSpacing = 60;

    int totalWidth = hand.size() * (cardWidth + cardSpacing) - cardSpacing;
    int startX = (ScreenSize::getWidth() - totalWidth) / 2;
    int yPos = ScreenSize::getHeigth() - cardHeight - 170;

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
            if (c->canPlay(p) && m_currentEnemy == e) {
                int cost = c->getCurrentCost(p);
                if (p->GETER_ENERGY() >= cost) {
                    if (c->GETER_TYPE() == ATTACK) {
                        QList<Enemy*> enemies;
                        enemies.append(e);
                        c->play(p, enemies);
                    } else {
                        QList<Enemy*> empty;
                        c->play(p, empty);
                    }
                    p->SPEND_ENERGY(cost);
                    p->REMOVE_FROM_HAND(c);
                    updateUI();
                }
            }
        });

        connect(card, &Card::Card_Dropped, this, [=](Card* c) {
            if (c->canPlay(p) && (c->GETER_TYPE() == SKILL || c->GETER_TYPE() == POWER)) {
                int cost = c->getCurrentCost(p);
                if (p->GETER_ENERGY() >= cost) {
                    QList<Enemy*> enemies;
                    if (m_currentEnemy) {
                        enemies.append(m_currentEnemy);
                    }
                    c->play(p, enemies);
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

void CombatScene::clearCards()
{
    for (auto item : m_cardItems) {
        m_scene->removeItem(item);
        disconnect(item, nullptr, this, nullptr);
    }
    m_cardItems.clear();
}

void CombatScene::updateUI()
{
    player* p = player::instance();
    if (p && m_playerAvatar) {
        QPixmap avatarPixmap = p->pixmap();
        if (!avatarPixmap.isNull()) {
            const int ITEM_SIZE = 180;
            QPixmap scaledPixmap = avatarPixmap.scaled(ITEM_SIZE, ITEM_SIZE,
                                                       Qt::KeepAspectRatio,
                                                       Qt::SmoothTransformation);
            m_playerAvatar->setPixmap(scaledPixmap);
        }
    }

    updateHPBar();
    updateEnergyLabel();
    updateEnemyUI();
    clearCards();
    setupPlayerCards();
}

void CombatScene::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    m_view->setGeometry(0, 0, width(), height());
    m_scene->setSceneRect(0, 0, width(), height());

    if (m_endTurnButton) {
        m_endTurnButton->setGeometry(ScreenSize::getWidth() - 150, 30, 120, 40);
    }
}

void CombatScene::updateBar()
{
    TopBar::instance(this)->setPlayerName(player::instance()->getName());
    TopBar::instance()->setGeometry(0, 0, ScreenSize::getWidth(), 40);
    TopBar::instance()->setHP(player::instance()->GETER_HP(), player::instance()->GETER_MAXHP());
    TopBar::instance()->setGold(player::instance()->GETER_GOLD());
    TopBar::instance()->setFloor(player::instance()->getFloor());
}