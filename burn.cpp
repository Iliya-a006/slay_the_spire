#include "burn.h"
#include"player.h"
#include"enemy.h"

Burn::Burn(QGraphicsItem *parent) : StatusCard(parent) {
    ID = 103;
    name = "Burn";
    energy_cost = -1;
    rarity = COMMON;
    description = "Unplayable. At end of your turn, if in hand: take 2 damage.";
    is_Exhaust = false;
    is_Ethereal = true;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Burn::Burn(const Burn& other) : StatusCard(other) {}

void Burn::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(player);
    Q_UNUSED(enemies);
}

Card* Burn::upgrade() {
    Burn* upgraded = new Burn(*this);
    upgraded->is_Upgrade = true;
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Burn::clone() const {
    return new Burn(*this);
}