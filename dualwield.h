#ifndef DUALWIELD_H
#define DUALWIELD_H

#include "skillcard.h"

class DualWield : public SkillCard
{
public:
    explicit DualWield(QGraphicsItem *parent = nullptr);
    DualWield(const DualWield& other);
    virtual ~DualWield() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // DUALWIELD_H