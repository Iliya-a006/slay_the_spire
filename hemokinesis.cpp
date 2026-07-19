#include "hemokinesis.h"
#include"player.h"
#include "enemy.h"
Hemokinesis::Hemokinesis(QGraphicsItem *parent) : Attack_Cards(parent) {
    ID = 4;
    name = "Hemokinesis";
    energy_cost = 1;
    rarity = UNCOMMON;
    damage = 15;
    description = "Lose 2 HP. Deal 15 damage.";
    is_Exhaust = false;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Hemokinesis::Hemokinesis(const Hemokinesis& other) : Attack_Cards(other) {}

void Hemokinesis::play(player* player, QList<Enemy*>& enemies) {
    player->LOSE_HP(2);
    int dmg = calculate_damage(player);
    applay_damage(player, enemies, dmg);
}

Card* Hemokinesis::upgrade() {
    Hemokinesis* upgraded = new Hemokinesis(*this);
    upgraded->damage += 5;
    upgraded->is_Upgrade = true;
    upgraded->description = "Lose 2 HP. Deal 20 damage.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Hemokinesis::clone() const {
    return new Hemokinesis(*this);
}