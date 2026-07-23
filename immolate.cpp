#include "immolate.h"
//#include "burn.h"
#include"enemy.h"
Immolate::Immolate(QGraphicsItem *parent) : Attack_Cards(parent) {
    ID = 8;
    name = "Immolate";
    energy_cost = 2;
    rarity = RARE;
    damage = 21;
    description = "Deal " + QString::number(damage) +
                  " damage to ALL enemies.\nAdd a *Burn into your discard pile.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Immolate::Immolate(const Immolate& other) : Attack_Cards(other) {}

void Immolate::play(player* player, QList<Enemy*>& enemies) {
    int dmg = calculate_damage(player);
    for (Enemy* e : enemies) {
        e->takeDamage(dmg);
    }
    for (int i = 0; i < 2; ++i) {
        //player->ADD_TO_DISCARDPILE(new Burn());
    }
}

Card* Immolate::upgrade() {
    Immolate* upgraded = new Immolate(*this);
    upgraded->damage += 7;
    upgraded->is_Upgrade = true;
    upgraded->description = "Deal " + QString::number(upgraded->damage) +
                            " damage to ALL enemies.\nAdd a *Burn into your discard pile.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Immolate::clone() const {
    return new Immolate(*this);
}