#ifndef STRIKE_H
#define STRIKE_H
#include "attack_cards.h"
class Strike:public Attack_Cards
{
public:
    explicit Strike(QGraphicsItem *parent = nullptr);
    Strike(const Strike& other);
    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // STRIKE_H
