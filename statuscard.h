#ifndef STATUSCARD_H
#define STATUSCARD_H

#include "card.h"

class StatusCard : public Card
{
public:
    explicit StatusCard(QGraphicsItem *parent = nullptr);
    StatusCard(const StatusCard& other);
    virtual ~StatusCard() = default;

    bool canPlay(player* player) const override;

    QString getCardTypeFolder() const override;
};

#endif // STATUSCARD_H
