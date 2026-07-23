#ifndef IMPERVIOUS_H
#define IMPERVIOUS_H

#include "skillcard.h"

class Impervious : public SkillCard
{
public:
    explicit Impervious(QGraphicsItem *parent = nullptr);
    Impervious(const Impervious& other);
    virtual ~Impervious() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // IMPERVIOUS_H