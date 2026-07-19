#include "bludgeon.h"
#include"player.h"
#include "enemy.h"
Bludgeon::Bludgeon(QGraphicsItem *parent) : Attack_Cards(parent) {
    ID = 7;
    name = "Bludgeon";
    energy_cost = 3;
    rarity = RARE;
    damage = 32;
    description = "Deal 32 damage.";
    is_Exhaust = false;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Bludgeon::Bludgeon(const Bludgeon& other) : Attack_Cards(other) {}

void Bludgeon::play(player* player, QList<Enemy*>& enemies) {
    int dmg = calculate_damage(player);
    applay_damage(player, enemies, dmg);
}

Card* Bludgeon::upgrade() {
    Bludgeon* upgraded = new Bludgeon(*this);
    upgraded->damage += 10;
    upgraded->is_Upgrade = true;
    upgraded->description = "Deal 42 damage.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Bludgeon::clone() const {
    return new Bludgeon(*this);
}