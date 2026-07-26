#ifndef BRUTALITY_H
#define BRUTALITY_H

#include "powercard.h"

class Brutality : public PowerCard
{
public:
    explicit Brutality(QGraphicsItem *parent = nullptr);
    Brutality(const Brutality& other);
    virtual ~Brutality() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    void applyPower(player* player) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // BRUTALITY_H