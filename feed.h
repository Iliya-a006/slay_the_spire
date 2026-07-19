#ifndef FEED_H
#define FEED_H

#include "attack_cards.h"

class Feed : public Attack_Cards
{
public:
    explicit Feed(QGraphicsItem *parent = nullptr);
    Feed(const Feed& other);
    virtual ~Feed() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // FEED_H