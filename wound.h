#ifndef WOUND_H
#define WOUND_H

#include "statuscard.h"

class Wound : public StatusCard
{
public:
    explicit Wound(QGraphicsItem *parent = nullptr);
    Wound(const Wound& other);
    virtual ~Wound() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // WOUND_H
