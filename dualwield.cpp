#include "dualwield.h"
#include"player.h"
#include"enemy.h"
DualWield::DualWield(QGraphicsItem *parent) : SkillCard(parent) {
    ID = 16;
    name = "Dual Wield";
    energy_cost = 1;
    rarity = UNCOMMON;
    block = 0;
    description = "Choose a card in hand - Add 2 copies into hand.";
    is_Exhaust = false;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

DualWield::DualWield(const DualWield& other) : SkillCard(other) {}

void DualWield::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    QVector<Card*>& hand = player->GETٍER_HAND();
    if (!hand.isEmpty()) {
        Card* card = hand.first();
        for (int i = 0; i < 2; ++i) {
            Card* clone = card->clone();
            player->ADD_TO_HAND(clone);
        }
    }
}

Card* DualWield::upgrade() {
    DualWield* upgraded = new DualWield(*this);
    upgraded->is_Upgrade = true;
    upgraded->description = "Choose a card in hand - Add 3 copies into hand.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* DualWield::clone() const {
    return new DualWield(*this);
}