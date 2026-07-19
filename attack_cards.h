#ifndef ATTACK_CARDS_H
#define ATTACK_CARDS_H
#include "card.h"
class Attack_Cards:public Card
{
public:
    explicit Attack_Cards(QGraphicsItem *parent=nullptr);
    virtual ~Attack_Cards()=default;
    Attack_Cards(const Attack_Cards& other);

    virtual int calculate_damage(const player* player) const;
    virtual void applay_damage(player* player,QList <Enemy*>& enemies,int damage);
};

#endif // ATTACK_CARDS_H
