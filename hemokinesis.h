#ifndef HEMOKINESIS_H
#define HEMOKINESIS_H

#include "attack_cards.h"
class Hemokinesis : public Attack_Cards
{
public:
    explicit Hemokinesis(QGraphicsItem *parent = nullptr);
    Hemokinesis(const Hemokinesis& other);
    virtual ~Hemokinesis() = default;

    void play(player* player, QList<Enemy*>& enemies) override;
    Card* upgrade() override;
    Card* clone() const override;
};

#endif // HEMOKINESIS_H