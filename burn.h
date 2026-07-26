#ifndef BURN_H
#define BURN_H

#include "statuscard.h"

class Burn : public StatusCard
{
public:
    explicit Burn(QGraphicsItem *parent = nullptr);
    Burn(const Burn& other);
    virtual ~Burn() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;

    int getBurnDamage() const { return burnDamage; }
    void setBurnDamage(int dmg);
private:
    int burnDamage=2;
};

#endif // BURN_H
