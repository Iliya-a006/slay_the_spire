#ifndef DARKEMBRACE_H
#define DARKEMBRACE_H

#include "powercard.h"

class DarkEmbrace : public PowerCard
{
public:
    explicit DarkEmbrace(QGraphicsItem *parent = nullptr);
    DarkEmbrace(const DarkEmbrace& other);
    virtual ~DarkEmbrace() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    void applyPower(player* player) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // DARKEMBRACE_H
