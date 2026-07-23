#include "defend.h"
#include "player.h"
#include "enemy.h"
Defend::Defend(QGraphicsItem *parent) : SkillCard(parent) {
    ID = 11;
    name = "Defend";
    energy_cost = 1;
    rarity = BASIC;
    block = 5;
    description = "Gain " + QString::number(block) + " block.";
    is_Exhaust = false;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Defend::Defend(const Defend& other) : SkillCard(other) {}

void Defend::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    int blk = calculateBlock(player);
    applyBlock(player, blk);
}

Card* Defend::upgrade() {
    Defend* upgraded = new Defend(*this);
    upgraded->block += 3;
    upgraded->is_Upgrade = true;
    upgraded->description = "Gain " + QString::number(upgraded->block) + " block.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Defend::clone() const {
    return new Defend(*this);
}