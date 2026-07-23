#include "impervious.h"
#include"player.h"
#include"enemy.h"
Impervious::Impervious(QGraphicsItem *parent) : SkillCard(parent) {
    ID = 15;
    name = "Impervious";
    energy_cost = 2;
    rarity = RARE;
    block = 30;
    description = "Gain " + QString::number(block) + " block - Exhaust.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Impervious::Impervious(const Impervious& other) : SkillCard(other) {}

void Impervious::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    int blk = calculateBlock(player);
    applyBlock(player, blk);
}

Card* Impervious::upgrade() {
    Impervious* upgraded = new Impervious(*this);
    upgraded->block += 10;
    upgraded->is_Upgrade = true;
    upgraded->description = "Gain " + QString::number(upgraded->block) + " block - Exhaust.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Impervious::clone() const {
    return new Impervious(*this);
}