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
    ~CombatScene();

    void setupCombat();
    void updateUI();

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void onEndTurnClicked();

private:
    QGraphicsScene* m_scene;
    QGraphicsView* m_view;
    QGraphicsPixmapItem* m_playerAvatar;
    QVector<Card*> m_cardItems;

    QGraphicsRectItem* m_hpBarBg;
    QGraphicsRectItem* m_hpBar;
    QGraphicsTextItem* m_hpText;

    QGraphicsTextItem* m_energyText;

    QPushButton* m_endTurnButton;

    void setupPlayerAvatar();
    void setupPlayerCards();
    void setupHPBar();
    void setupEnergyLabel();
    void setupEndTurnButton();
    void updateHPBar();
    void updateEnergyLabel();
    void clearCards();
    void endTurn();

    void connectPlayerSignals();
};

#endif // COMBATSCENE_H