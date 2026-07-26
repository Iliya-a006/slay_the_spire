#include "brutality.h"
#include"player.h"
#include"enemy.h"
#include"buff_debuff.h"
Brutality::Brutality(QGraphicsItem *parent) : PowerCard(parent) {
    ID = 24;
    name = "Brutality";
    energy_cost = 0;
    rarity = RARE;
    description = "At the start of your\nturn, lose 1 HP and\ndraw 1 card.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Brutality::Brutality(const Brutality& other) : PowerCard(other) {}

void Brutality::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    applyPower(player);
}

void Brutality::applyPower(player* player) {
    player->ADD_BUFF(BuffType::Brutality, 1, -1);
}

Card* Brutality::upgrade() {
    Brutality* upgraded = new Brutality(*this);
    upgraded->is_Upgrade = true;
    upgraded->description = "At the start of your\nturn, lose 1 HP and\ndraw 1 card.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Brutality::clone() const {
    return new Brutality(*this);
}