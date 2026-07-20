#include "combatscene.h"
#include "screensize.h"
#include <QVBoxLayout>

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
}

CombatScene::~CombatScene()
{
    clearCards();
    if (m_playerAvatar) {
        m_scene->removeItem(m_playerAvatar);
        delete m_playerAvatar;
        m_playerAvatar = nullptr;
    }
}

void CombatScene::setupCombat()
{
    setupPlayerAvatar();
    setupPlayerCards();
}

void CombatScene::updateUI()
{
    player* p = player::instance();
    if (p && m_playerAvatar) {
        m_playerAvatar->setPixmap(p->pixmap());
    }

    clearCards();
    setupPlayerCards();
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

    m_playerAvatar = new QGraphicsPixmapItem();
    m_playerAvatar->setPixmap(p->pixmap());
    m_playerAvatar->setScale(0.8);

    int avatarX = 50;
    int avatarY = (ScreenSize::getHeigth() / 2) - 50;
    m_playerAvatar->setPos(avatarX, avatarY);
    m_scene->addItem(m_playerAvatar);
}

void CombatScene::setupPlayerCards()
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

    // ===== کارت‌ها رو ۵۰ پیکسل بالا تر ببر =====
    int yPos = ScreenSize::getHeigth() - cardHeight - 80;  // از 30 به 80 تغییر کرد

    for (int i = 0; i < hand.size(); ++i) {
        Card* card = hand[i];
        if (!card) continue;

        card->setPos(startX + i * (cardWidth + cardSpacing), yPos);
        card->setScale(0.5);
        card->Set_Original_Position(startX + i * (cardWidth + cardSpacing), yPos);
        card->setAcceptHoverEvents(true);
        card->setFlag(QGraphicsItem::ItemIsSelectable, false);
        card->setFlag(QGraphicsItem::ItemIsMovable, true);
        m_scene->addItem(card);
        m_cardItems.append(card);
    }
}

void CombatScene::clearCards()
{
    for (auto item : m_cardItems) {
        m_scene->removeItem(item);
    }
    m_cardItems.clear();
}

void CombatScene::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    m_view->setGeometry(0, 0, width(), height());
    m_scene->setSceneRect(0, 0, width(), height());
}