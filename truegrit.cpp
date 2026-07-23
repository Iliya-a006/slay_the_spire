#include "truegrit.h"
#include"player.h"
#include"enemy.h"
#include<QRandomGenerator>
TrueGrit::TrueGrit(QGraphicsItem *parent) : SkillCard(parent) {
    ID = 19;
    name = "True Grit";
    energy_cost = 1;
    rarity = COMMON;
    block = 8;
    description = "Gain " + QString::number(block) + " block - Exhaust a random card in hand.";
    is_Exhaust = false;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

TrueGrit::TrueGrit(const TrueGrit& other) : SkillCard(other) {}

void TrueGrit::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    int blk = calculateBlock(player);
    applyBlock(player, blk);

    QVector<Card*>& hand = player->GETٍER_HAND();
    if (!hand.isEmpty()) {
        int randomIndex = QRandomGenerator::global()->bounded(hand.size());
        Card* card = hand.takeAt(randomIndex);
        player->ADD_TO_EXHAUSTPILE(card);
    }
}

Card* TrueGrit::upgrade() {
    TrueGrit* upgraded = new TrueGrit(*this);
    upgraded->block += 3;
    upgraded->is_Upgrade = true;
    upgraded->description = "Gain " + QString::number(upgraded->block) + " block - Exhaust a random card in hand.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* TrueGrit::clone() const {
    return new TrueGrit(*this);
}