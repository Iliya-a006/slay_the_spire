#ifndef BERSERK_H
#define BERSERK_H

#include "powercard.h"

class Berserk : public PowerCard
{
public:
    explicit Berserk(QGraphicsItem *parent = nullptr);
    Berserk(const Berserk& other);
    virtual ~Berserk() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    void applyPower(player* player) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // BERSERK_H
