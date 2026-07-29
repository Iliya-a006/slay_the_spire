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

};

#endif // ENEMYSCENE_H