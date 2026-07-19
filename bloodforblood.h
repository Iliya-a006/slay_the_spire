#ifndef BLOODFORBLOOD_H
#define BLOODFORBLOOD_H

#include "attack_cards.h"

class BloodForBlood : public Attack_Cards
{
public:
    explicit BloodForBlood(QGraphicsItem *parent = nullptr);
    BloodForBlood(const BloodForBlood& other);
    virtual ~BloodForBlood() = default;

    int getCurrentCost( player* player) const override;
    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // BLOODFORBLOOD_H