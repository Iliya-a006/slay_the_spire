#include "enemyscene.h"
#include "screensize.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>

EnemyScene::EnemyScene(QWidget *parent)
    : CombatScene(parent),
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

    m_enemyItem = nullptr;
    m_enemyHPText = nullptr;
    m_enemyIntentText = nullptr;
}

EnemyScene::~EnemyScene()
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
}

void EnemyScene::setupCombat()
{
    CombatScene::setupCombat();
    setupEnemy();
    updateUI();
}

void EnemyScene::setEnemy(Enemy* enemy)
{
    m_currentEnemy = enemy;
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

void EnemyScene::updateUI()
{
    CombatScene::updateUI();
    updateEnemyUI();
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
    m_view->setGeometry(0, 0, width(), height());
    m_scene->setSceneRect(0, 0, width(), height());

    if (m_endTurnButton) {
        m_endTurnButton->setGeometry(ScreenSize::getWidth() - 150, 30, 120, 40);
    }
}