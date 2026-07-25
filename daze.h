#ifndef DAZE_H
#define DAZE_H

#include "statuscard.h"

class Daze : public StatusCard
{
public:
    explicit Daze(QGraphicsItem *parent = nullptr);
    Daze(const Daze& other);
    virtual ~Daze() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // DAZE_H
