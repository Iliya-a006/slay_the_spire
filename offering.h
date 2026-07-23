#ifndef OFFERING_H
#define OFFERING_H

#include "skillcard.h"

class Offering : public SkillCard
{
public:
    explicit Offering(QGraphicsItem *parent = nullptr);
    Offering(const Offering& other);
    virtual ~Offering() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // OFFERING_H