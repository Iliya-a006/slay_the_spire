#ifndef EXHUME_H
#define EXHUME_H

#include "skillcard.h"

class Exhume : public SkillCard
{
public:
    explicit Exhume(QGraphicsItem *parent = nullptr);
    Exhume(const Exhume& other);
    virtual ~Exhume() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // EXHUME_H