#ifndef LIMITBREAK_H
#define LIMITBREAK_H

#include "skillcard.h"

class LimitBreak : public SkillCard
{
public:
    explicit LimitBreak(QGraphicsItem *parent = nullptr);
    LimitBreak(const LimitBreak& other);
    virtual ~LimitBreak() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // LIMITBREAK_H