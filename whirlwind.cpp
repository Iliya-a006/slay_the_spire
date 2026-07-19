#include "whirlwind.h"
#include"player.h"
#include"enemy.h"
Whirlwind::Whirlwind(QGraphicsItem *parent) : Attack_Cards(parent) {
    ID = 6;
    name = "Whirlwind";
    energy_cost = 0;
    rarity = UNCOMMON;
    damage = 5;
    description = "Deal 5 damage to all enemies X times. X = all current energy.";
    is_Exhaust = false;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Whirlwind::Whirlwind(const Whirlwind& other) : Attack_Cards(other) {}

int Whirlwind::getCurrentCost(player* player) const {
    return player->GETER_SETER_ENERGY();
}

void Whirlwind::play(player* player, QList<Enemy*>& enemies) {
    int energyUsed = player->GETER_SETER_ENERGY();
    player->SPEND_ENERGY(energyUsed);
    int dmg = calculate_damage(player);
    for (int i = 0; i < energyUsed; ++i) {
        for (Enemy* e : enemies) {
            e->takeDamage(dmg);
        }
    }
}

Card* Whirlwind::upgrade() {
    Whirlwind* upgraded = new Whirlwind(*this);
    upgraded->damage += 3;
    upgraded->is_Upgrade = true;
    upgraded->description = "Deal 8 damage to all enemies X times. X = all current energy.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Whirlwind::clone() const {
    return new Whirlwind(*this);
}