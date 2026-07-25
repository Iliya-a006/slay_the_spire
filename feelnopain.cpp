#include "feelnopain.h"
#include"player.h"
#include"enemy.h"
#include"buff_debuff.h"
FeelNoPain::FeelNoPain(QGraphicsItem *parent) : PowerCard(parent) {
    ID = 25;
    name = "Feel No Pain";
    energy_cost = 1;
    rarity = UNCOMMON;
    description = "Every time a card is Exhausted, gain 3 block.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

FeelNoPain::FeelNoPain(const FeelNoPain& other) : PowerCard(other) {}

void FeelNoPain::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    applyPower(player);
}

void FeelNoPain::applyPower(player* player) {
    player->ADD_BUFF(BuffType::FeelNoPain, 3, -1);
}

Card* FeelNoPain::upgrade() {
    FeelNoPain* upgraded = new FeelNoPain(*this);
    upgraded->is_Upgrade = true;
    upgraded->description = "Every time a card is Exhausted, gain 4 block.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* FeelNoPain::clone() const {
    return new FeelNoPain(*this);
}