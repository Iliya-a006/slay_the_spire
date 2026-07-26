#include "barricade.h"
#include"player.h"
#include"enemy.h"
#include"buff_debuff.h"
Barricade::Barricade(QGraphicsItem *parent) : PowerCard(parent) {
    ID = 26;
    name = "Barricade";
    energy_cost = 3;
    rarity = RARE;
    description = "Block is not removed at\nthe start of your turn.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Barricade::Barricade(const Barricade& other) : PowerCard(other) {}

void Barricade::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    applyPower(player);
}

void Barricade::applyPower(player* player) {
    player->ADD_BUFF(BuffType::Barricade, 1, -1);
}

Card* Barricade::upgrade() {
    Barricade* upgraded = new Barricade(*this);
    upgraded->energy_cost = 2;
    upgraded->is_Upgrade = true;
    upgraded->description = "Block is not removed at\nthe start of your turn.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Barricade::clone() const {
    return new Barricade(*this);
}