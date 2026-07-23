#ifndef ENTRENCH_H
#define ENTRENCH_H

#include "skillcard.h"

class Entrench : public SkillCard
{
public:
    explicit Entrench(QGraphicsItem *parent = nullptr);
    Entrench(const Entrench& other);
    virtual ~Entrench() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // ENTRENCH_H