#ifndef BLUDGEON_H
#define BLUDGEON_H

#include "attack_cards.h"


class Bludgeon : public Attack_Cards
{
public:
    explicit Bludgeon(QGraphicsItem *parent = nullptr);
    Bludgeon(const Bludgeon& other);
    virtual ~Bludgeon() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // BLUDGEON_H