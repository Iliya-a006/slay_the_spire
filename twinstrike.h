#ifndef TWINSTRIKE_H
#define TWINSTRIKE_H

#include "attack_cards.h"

class TwinStrike : public Attack_Cards
{
public:
    explicit TwinStrike(QGraphicsItem *parent = nullptr);
    TwinStrike(const TwinStrike& other);
    virtual ~TwinStrike() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // TWINSTRIKE_H