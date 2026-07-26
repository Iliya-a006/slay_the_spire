#include "slime.h"
#include"player.h"
#include"enemy.h"
Slime::Slime(QGraphicsItem *parent) : StatusCard(parent) {
    ID = 101;
    name = "Slime";
    energy_cost = 1;
    rarity = COMMON;
    description = "Exhaust.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Slime::Slime(const Slime& other) : StatusCard(other) {}

void Slime::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(player);
    Q_UNUSED(enemies);
}

Card* Slime::upgrade() {
    Slime* upgraded = new Slime(*this);
    upgraded->is_Upgrade = true;
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Slime::clone() const {
    return new Slime(*this);
}