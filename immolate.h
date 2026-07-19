#ifndef IMMOLATE_H
#define IMMOLATE_H

#include "attack_cards.h"

class Immolate : public Attack_Cards
{
public:
    explicit Immolate(QGraphicsItem *parent = nullptr);
    Immolate(const Immolate& other);
    virtual ~Immolate() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // IMMOLATE_H