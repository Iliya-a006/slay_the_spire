#include "inflame.h"
#include"player.h"
#include"enemy.h"
Inflame::Inflame(QGraphicsItem *parent) : PowerCard(parent) {
    ID = 21;
    name = "Inflame";
    energy_cost = 1;
    rarity = UNCOMMON;
    description = "Gain 2 Strength.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Inflame::Inflame(const Inflame& other) : PowerCard(other) {}

void Inflame::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    applyPower(player);
}

void Inflame::applyPower(player* player) {
    player->ADD_BUFF(BuffType::Strength, 2, -1);
}

Card* Inflame::upgrade() {
    Inflame* upgraded = new Inflame(*this);
    upgraded->is_Upgrade = true;
    upgraded->description = "Gain 3 Strength.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Inflame::clone() const {
    return new Inflame(*this);
}