#include "daze.h"
#include"player.h"
#include"enemy.h"
Daze::Daze(QGraphicsItem *parent) : StatusCard(parent) {
    ID = 100;
    name = "Daze";
    energy_cost = -1;
    rarity = COMMON;
    description = "Unplayable - Ethereal.";
    is_Exhaust = false;
    is_Ethereal = true;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Daze::Daze(const Daze& other) : StatusCard(other) {}

void Daze::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(player);
    Q_UNUSED(enemies);
}

Card* Daze::upgrade() {
    Daze* upgraded = new Daze(*this);
    upgraded->is_Upgrade = true;
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Daze::clone() const {
    return new Daze(*this);
}