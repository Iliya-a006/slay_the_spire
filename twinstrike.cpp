#include "twinstrike.h"
#include"player.h"
#include"enemy.h"
TwinStrike::TwinStrike(QGraphicsItem *parent) : Attack_Cards(parent) {
    ID = 2;
    name = "Twin Strike";
    energy_cost = 1;
    rarity = COMMON;
    damage = 6;
    description = "Deal " + QString::number(damage) + " damage twice.";
    is_Exhaust = false;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

TwinStrike::TwinStrike(const TwinStrike& other) : Attack_Cards(other) {}

void TwinStrike::play(player* player, QList<Enemy*>& enemies) {
    int dmg = calculate_damage(player);
    for (int i = 0; i < 2; ++i) {
        applay_damage(player, enemies, dmg);
    }
}

Card* TwinStrike::upgrade() {
    TwinStrike* upgraded = new TwinStrike(*this);
    upgraded->damage += 4;
    upgraded->is_Upgrade = true;
    upgraded->description = "Deal " + QString::number(upgraded->damage) + " damage twice.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* TwinStrike::clone() const {
    return new TwinStrike(*this);
}