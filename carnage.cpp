#include "carnage.h"
#include "player.h"
#include"enemy.h"
Carnage::Carnage(QGraphicsItem *parent) : Attack_Cards(parent) {
    ID = 5;
    name = "Carnage";
    energy_cost = 2;
    rarity = UNCOMMON;
    damage = 20;
    description = "Ethereal.\nDeal " + QString::number(damage) + " damage.";
    is_Exhaust = false;
    is_Ethereal = true;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Carnage::Carnage(const Carnage& other) : Attack_Cards(other) {}

void Carnage::play(player* player, QList<Enemy*>& enemies) {
    int dmg = calculate_damage(player);
    applay_damage(player, enemies, dmg);
}

Card* Carnage::upgrade() {
    Carnage* upgraded = new Carnage(*this);
    upgraded->damage += 8;
    upgraded->is_Upgrade = true;
    upgraded->description = "Ethereal.\nDeal " + QString::number(upgraded->damage) + " damage.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Carnage::clone() const {
    return new Carnage(*this);
}