#ifndef SLIME_H
#define SLIME_H

#include "statuscard.h"

class Slime : public StatusCard
{
public:
    explicit Slime(QGraphicsItem *parent = nullptr);
    Slime(const Slime& other);
    virtual ~Slime() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // SLIME_H
