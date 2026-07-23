#ifndef TRUEGRIT_H
#define TRUEGRIT_H

#include "skillcard.h"

class TrueGrit : public SkillCard
{
public:
    explicit TrueGrit(QGraphicsItem *parent = nullptr);
    TrueGrit(const TrueGrit& other);
    virtual ~TrueGrit() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // TRUEGRIT_H