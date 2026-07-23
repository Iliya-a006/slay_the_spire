#include "shrugitoff.h"
#include"player.h"
#include"enemy.h"
ShrugItOff::ShrugItOff(QGraphicsItem *parent) : SkillCard(parent) {
    ID = 20;
    name = "Shrug It Off";
    energy_cost = 1;
    rarity = COMMON;
    block = 8;
    description = "Draw 1 card - Gain " + QString::number(block) + " block.";
    is_Exhaust = false;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

ShrugItOff::ShrugItOff(const ShrugItOff& other) : SkillCard(other) {}

void ShrugItOff::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    player->DRAW_CARD(1);
    int blk = calculateBlock(player);
    applyBlock(player, blk);
}

Card* ShrugItOff::upgrade() {
    ShrugItOff* upgraded = new ShrugItOff(*this);
    upgraded->block += 3;
    upgraded->is_Upgrade = true;
    upgraded->description = "Draw 1 card - Gain " + QString::number(upgraded->block) + " block.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* ShrugItOff::clone() const {
    return new ShrugItOff(*this);
}