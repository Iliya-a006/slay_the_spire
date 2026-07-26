#ifndef METALLICIZE_H
#define METALLICIZE_H

#include "powercard.h"

class Metallicize : public PowerCard
{
public:
    explicit Metallicize(QGraphicsItem *parent = nullptr);
    Metallicize(const Metallicize& other);
    virtual ~Metallicize() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    void applyPower(player* player) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // METALLICIZE_H