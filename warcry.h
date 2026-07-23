#ifndef WARCRY_H
#define WARCRY_H

#include "skillcard.h"

class Warcry : public SkillCard
{
public:
    explicit Warcry(QGraphicsItem *parent = nullptr);
    Warcry(const Warcry& other);
    virtual ~Warcry() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // WARCRY_H