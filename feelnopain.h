#ifndef FEELNOPAIN_H
#define FEELNOPAIN_H

#include "powercard.h"

class FeelNoPain : public PowerCard
{
public:
    explicit FeelNoPain(QGraphicsItem *parent = nullptr);
    FeelNoPain(const FeelNoPain& other);
    virtual ~FeelNoPain() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    void applyPower(player* player) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // FEELNOPAIN_H
