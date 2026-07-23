#ifndef ENEMYSCENE_H
#define ENEMYSCENE_H

#include "combatscene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QVector>
#include "player.h"
#include "card.h"
#include "enemy.h"

class EnemyScene : public CombatScene
{
    Q_OBJECT

public:
    explicit EnemyScene(QWidget *parent = nullptr);
    ~EnemyScene();

    void setupCombat() override;
    void setEnemy(Enemy* enemy);
    void updateUI() override;

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void onEndTurnClicked();

private:
    Enemy* m_currentEnemy;
    QGraphicsPixmapItem* m_enemyItem;
    QGraphicsTextItem* m_enemyHPText;
    QGraphicsTextItem* m_enemyIntentText;

    void setupEnemy();
    void updateEnemyUI();
    void endTurn();
};

#endif // ENEMYSCENE_H