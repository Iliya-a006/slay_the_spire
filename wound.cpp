#include "wound.h"
#include"player.h"
#include"enemy.h"
Wound::Wound(QGraphicsItem *parent) : StatusCard(parent) {
    ID = 102;
    name = "Wound";
    energy_cost = -1;
    rarity = COMMON;
    description = "Unplayable.";
    is_Exhaust = false;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Wound::Wound(const Wound& other) : StatusCard(other) {}

void Wound::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(player);
    Q_UNUSED(enemies);
}

Card* Wound::upgrade() {
    Wound* upgraded = new Wound(*this);
    upgraded->is_Upgrade = true;
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Wound::clone() const {
    return new Wound(*this);
}