#include "darkembrace.h"
#include"player.h"
#include"enemy.h"
#include"buff_debuff.h"
DarkEmbrace::DarkEmbrace(QGraphicsItem *parent) : PowerCard(parent) {
    ID = 27;
    name = "Dark Embrace";
    energy_cost = 2;
    rarity = UNCOMMON;
    description = "Whenever a card is Exhausted,\ndraw 1 card.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

DarkEmbrace::DarkEmbrace(const DarkEmbrace& other) : PowerCard(other) {}

void DarkEmbrace::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    applyPower(player);
}

void DarkEmbrace::applyPower(player* player) {
    player->ADD_BUFF(BuffType::DarkEmbrace, 1, -1);
}

Card* DarkEmbrace::upgrade() {
    DarkEmbrace* upgraded = new DarkEmbrace(*this);
    upgraded->energy_cost = 1;
    upgraded->is_Upgrade = true;
    upgraded->description = "Whenever a card is Exhausted,\ndraw 1 card.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* DarkEmbrace::clone() const {
    return new DarkEmbrace(*this);
}