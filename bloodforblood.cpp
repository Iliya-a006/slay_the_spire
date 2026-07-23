#include "bloodforblood.h"
#include"player.h"
#include "enemy.h"
BloodForBlood::BloodForBlood(QGraphicsItem *parent) : Attack_Cards(parent) {
    ID = 3;
    name = "Blood for Blood";
    energy_cost = 4;
    rarity = UNCOMMON;
    damage = 18;
    description = "Costs 1 less R\nfor each time you lose HP this combat.\nDeal " + QString::number(damage) + " damage.";
    is_Exhaust = false;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

BloodForBlood::BloodForBlood(const BloodForBlood& other) : Attack_Cards(other) {}

int BloodForBlood::getCurrentCost( player* player) const {
    int reduction = player->GETER_UNBLOCKEDDAMAGETAKEN();
    return qMax(1, energy_cost - reduction);
}

void BloodForBlood::play(player* player, QList<Enemy*>& enemies) {
    int dmg = calculate_damage(player);
    applay_damage(player, enemies, dmg);
}

Card* BloodForBlood::upgrade() {
    BloodForBlood* upgraded = new BloodForBlood(*this);
    upgraded->damage += 6;
    upgraded->is_Upgrade = true;
    upgraded->description = "Costs 1 less R\nfor each time you lose HP this combat.\nDeal " + QString::number(upgraded->damage) + " damage.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* BloodForBlood::clone() const {
    return new BloodForBlood(*this);
}