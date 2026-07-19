#ifndef WHIRLWIND_H
#define WHIRLWIND_H

#include "attack_cards.h"

class Whirlwind : public Attack_Cards
{
public:
    explicit Whirlwind(QGraphicsItem *parent = nullptr);
    Whirlwind(const Whirlwind& other);
    virtual ~Whirlwind() = default;

    int getCurrentCost( player* player) const override;
    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // WHIRLWIND_H