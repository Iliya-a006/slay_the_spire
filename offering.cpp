#include "offering.h"
#include"player.h"
#include"enemy.h"
Offering::Offering(QGraphicsItem *parent) : SkillCard(parent) {
    ID = 14;
    name = "Offering";
    energy_cost = 0;
    rarity = RARE;
    block = 0;
    description = "Lose 6 HP - Gain 2 Energy - Draw 3 cards - Exhaust.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Offering::Offering(const Offering& other) : SkillCard(other) {}

void Offering::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    player->LOSE_HP(6);
    player->GETER_SETER_ENERGY() += 2;
    player->DRAW_CARD(3);
}

Card* Offering::upgrade() {
    Offering* upgraded = new Offering(*this);
    upgraded->is_Upgrade = true;
    upgraded->description = "Lose 6 HP - Gain 2 Energy - Draw 3 cards - Exhaust.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Offering::clone() const {
    return new Offering(*this);
}