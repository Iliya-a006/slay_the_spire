#ifndef BARRICADE_H
#define BARRICADE_H

#include "powercard.h"

class Barricade : public PowerCard
{
public:
    explicit Barricade(QGraphicsItem *parent = nullptr);
    Barricade(const Barricade& other);
    virtual ~Barricade() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    void applyPower(player* player) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // BARRICADE_H
