#ifndef CARNAGE_H
#define CARNAGE_H

#include "attack_cards.h"


class Carnage : public Attack_Cards
{
public:
    explicit Carnage(QGraphicsItem *parent = nullptr);
    Carnage(const Carnage& other);
    virtual ~Carnage() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // CARNAGE_H