#include "limitbreak.h"
#include "player.h"
#include"enemy.h"
LimitBreak::LimitBreak(QGraphicsItem *parent) : SkillCard(parent) {
    ID = 13;
    name = "Limit Break";
    energy_cost = 1;
    rarity = RARE;
    block = 0;
    description = "Double your Strength - Exhaust.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

LimitBreak::LimitBreak(const LimitBreak& other) : SkillCard(other) {}

void LimitBreak::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    int currentStrength = player->GETER_STRENGtH();
    player->ADD_STRENGtH(currentStrength);
}

Card* LimitBreak::upgrade() {
    LimitBreak* upgraded = new LimitBreak(*this);
    upgraded->is_Upgrade = true;
    upgraded->description = "Double your Strength - Exhaust.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* LimitBreak::clone() const {
    return new LimitBreak(*this);
}