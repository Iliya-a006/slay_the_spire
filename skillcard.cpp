#include "skillcard.h"
#include "player.h"
SkillCard::SkillCard(QGraphicsItem *parent) : Card(parent) {
    type = SKILL;
}

SkillCard::SkillCard(const SkillCard& other) : Card(other) {}

int SkillCard::calculateBlock(const player* player) const {
    int blk = block + player->GETER_DEXTERITY();
    return blk;
}

void SkillCard::applyBlock(player* player, int block) {
    player->ADD_BLOCK(block);
}

QString SkillCard::getCardTypeFolder() const {
    return "SKILL_CARDS";
}