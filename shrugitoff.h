#ifndef SHRUGITOFF_H
#define SHRUGITOFF_H

#include "skillcard.h"

class ShrugItOff : public SkillCard
{
public:
    explicit ShrugItOff(QGraphicsItem *parent = nullptr);
    ShrugItOff(const ShrugItOff& other);
    virtual ~ShrugItOff() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // SHRUGITOFF_H