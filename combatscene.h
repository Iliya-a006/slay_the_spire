#ifndef COMBATSCENE_H
#define COMBATSCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QVector>
#include "player.h"
#include "card.h"
#include "enemy.h"

class CombatScene : public QWidget
{
    Q_OBJECT

public:
    explicit CombatScene(QWidget *parent = nullptr);
    virtual ~CombatScene();

    virtual void setupCombat();
    virtual void updateUI();

protected:
    QGraphicsScene* m_scene;
    QGraphicsView* m_view;
    QGraphicsPixmapItem* m_playerAvatar;
    QVector<Card*> m_cardItems;

    QGraphicsRectItem* m_hpBarBg;
    QGraphicsRectItem* m_hpBar;
    QGraphicsTextItem* m_hpText;
    QGraphicsTextItem* m_energyText;
    QPushButton* m_endTurnButton;

    virtual void setupPlayerAvatar();
    virtual void setupPlayerCards();
    virtual void setupHPBar();
    virtual void setupEnergyLabel();
    virtual void setupEndTurnButton();
    virtual void updateHPBar();
    virtual void updateEnergyLabel();
    virtual void clearCards();
    virtual void endTurn();
    virtual void connectPlayerSignals();

    void resizeEvent(QResizeEvent* event) override;

private slots:
    void onEndTurnClicked();
};

#endif // COMBATSCENE_H