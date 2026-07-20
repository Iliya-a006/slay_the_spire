#ifndef COMBATSCENE_H
#define COMBATSCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QVector>
#include "player.h"
#include "card.h"

class CombatScene : public QWidget
{
    Q_OBJECT

public:
    explicit CombatScene(QWidget *parent = nullptr);
    ~CombatScene();

    void setupCombat();
    void updateUI();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QGraphicsScene* m_scene;
    QGraphicsView* m_view;
    QGraphicsPixmapItem* m_playerAvatar;
    QVector<Card*> m_cardItems;  // ===== الان از نوع Card* هست =====

    void setupPlayerAvatar();
    void setupPlayerCards();
    void clearCards();
};

#endif // COMBATSCENE_H