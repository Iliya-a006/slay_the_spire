#ifndef INFLAME_H
#define INFLAME_H

#include "powercard.h"

class Inflame : public PowerCard
{
public:
    explicit Inflame(QGraphicsItem *parent = nullptr);
    Inflame(const Inflame& other);
    virtual ~Inflame() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    void applyPower(player* player) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // INFLAME_H