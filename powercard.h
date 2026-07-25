#ifndef POWERCARD_H
#define POWERCARD_H

#include "card.h"

class PowerCard : public Card
{
public:
    explicit PowerCard(QGraphicsItem *parent = nullptr);
    PowerCard(const PowerCard& other);
    virtual ~PowerCard() = default;

    virtual void applyPower(player* player) = 0;

    QString getCardTypeFolder() const override;
};

#endif // POWERCARD_H