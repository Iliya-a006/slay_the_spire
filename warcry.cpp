#include "warcry.h"
#include"player.h"
#include"enemy.h"
Warcry::Warcry(QGraphicsItem *parent) : SkillCard(parent) {
    ID = 18;
    name = "Warcry";
    energy_cost = 0;
    rarity = COMMON;
    block = 0;
    description = "Draw 1 card - Put a card from hand on top of draw pile - Exhaust.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Warcry::Warcry(const Warcry& other) : SkillCard(other) {}

void Warcry::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    player->DRAW_CARD(1);
    QVector<Card*>& hand = player->GETٍER_HAND();
    if (!hand.isEmpty()) {
        Card* card = hand.takeLast();
        player->ADD_TO_DRAWPILE(card);
    }
}

Card* Warcry::upgrade() {
    Warcry* upgraded = new Warcry(*this);
    upgraded->is_Upgrade = true;
    upgraded->description = "Draw 2 cards - Put a card from hand on top of draw pile - Exhaust.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Warcry::clone() const {
    return new Warcry(*this);
}