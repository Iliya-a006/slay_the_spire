#include "enemyscene.h"
#include "screensize.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "cultist.h"

EnemyScene::EnemyScene(QWidget *parent)
    : CombatScene(parent)
{
    QPixmap bg(":/prefix1/images/battleBg.png");
    QPixmap scaledBg = bg.scaled(ScreenSize::getSize(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *bgItem = m_scene->addPixmap(scaledBg);
    bgItem->setZValue(-100);
    bgItem->setPos(0, 0);
}

void EnemyScene::resetRoom()
{
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