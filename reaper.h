#ifndef REAPER_H
#define REAPER_H

#include "attack_cards.h"

class Reaper : public Attack_Cards
{
public:
    explicit Reaper(QGraphicsItem *parent = nullptr);
    Reaper(const Reaper& other);
    virtual ~Reaper() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // REAPER_H