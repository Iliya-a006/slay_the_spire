#include "entrench.h"
#include"player.h"
#include"enemy.h"
Entrench::Entrench(QGraphicsItem *parent) : SkillCard(parent) {
    ID = 17;
    name = "Entrench";
    energy_cost = 2;
    rarity = UNCOMMON;
    block = 0;
    description = "Double your Block.";
    is_Exhaust = false;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Entrench::Entrench(const Entrench& other) : SkillCard(other) {}

void Entrench::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    int currentBlock = player->GETER_BLOCK();
    player->ADD_BLOCK(currentBlock);
}

Card* Entrench::upgrade() {
    Entrench* upgraded = new Entrench(*this);
    upgraded->energy_cost = 1;
    upgraded->is_Upgrade = true;
    upgraded->description = "Double your Block.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Entrench::clone() const {
    return new Entrench(*this);
}