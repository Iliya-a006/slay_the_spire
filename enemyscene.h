#ifndef ENEMYSCENE_H
#define ENEMYSCENE_H

#include "combatscene.h"

class EnemyScene : public CombatScene
{
    Q_OBJECT

public:
    explicit EnemyScene(QWidget *parent = nullptr);
    ~EnemyScene();

    void setupCombat() override;
    void updateUI() override;

    void resetRoom() override;

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void onEndTurnClicked();

private:
    void endTurn();

private:
    QGraphicsPixmapItem* coinItem;
    QGraphicsRectItem* dimmer;
    QLabel* topLabel;
    QLabel* victoryLabel;
    QLabel* countLabel;
    QLabel* nameLabel;
    QPushButton* nextbutton;
    QPushButton* leaveButton;
    QVector<Card*> availableCards;
    Card* m_selectedCard = nullptr;
    bool is_end;
    int NOfGolds;

    void endRoom(bool result);
    void goldGift();
    void cardGift();
    void showItems();
    Card* pickRandomCard();
    void deleteScene();

private slots:
        void onCardClicked(Card* card);

};

#endif // ENEMYSCENE_H