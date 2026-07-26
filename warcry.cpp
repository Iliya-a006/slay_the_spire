#include "warcry.h"
#include "player.h"
#include "enemy.h"
#include <QRandomGenerator>
Warcry::Warcry(QGraphicsItem *parent) : SkillCard(parent) {
    ID = 18;
    name = "Warcry";
    energy_cost = 0;
    rarity = COMMON;
    block = 0;
    description = "Draw 1 card.\nPut a card from your hand onto the top of your draw pile.\nExhaust.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Warcry::Warcry(const Warcry& other) : SkillCard(other) {}

void Warcry::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);

    // ===== کشیدن کارت =====
    if (is_Upgrade) {
        player->DRAW_CARD(2);
    } else {
        player->DRAW_CARD(1);
    }
    QVector<Card*>& hand = player->GETٍER_HAND();
    if (!hand.isEmpty()) {
        int randomIndex = QRandomGenerator::global()->bounded(hand.size());
        Card* card = hand.takeAt(randomIndex);
        player->ADD_TO_DRAWPILE(card);
    }
}

Card* Warcry::upgrade() {
    Warcry* upgraded = new Warcry(*this);
    upgraded->is_Upgrade = true;
    upgraded->description = "Draw 2 cards.\nPut a card from your hand onto the top of your draw pile.\nExhaust.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Warcry::clone() const {
    return new Warcry(*this);
}