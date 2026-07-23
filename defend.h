#ifndef DEFEND_H
#define DEFEND_H

#include "skillcard.h"

class Defend : public SkillCard
{
public:
    explicit Defend(QGraphicsItem *parent = nullptr);
    Defend(const Defend& other);
    virtual ~Defend() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // DEFEND_H