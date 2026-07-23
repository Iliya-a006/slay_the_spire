#include "exhume.h"
#include"player.h"
#include"enemy.h"
Exhume::Exhume(QGraphicsItem *parent) : SkillCard(parent) {
    ID = 12;
    name = "Exhume";
    energy_cost = 1;
    rarity = RARE;
    block = 0;
    description = "Put a card from exhaust pile into hand - Exhaust.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Exhume::Exhume(const Exhume& other) : SkillCard(other) {}

void Exhume::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    QVector<Card*>& exhaustPile = player->GETٍER_EXHAUSTPILE();
    if (!exhaustPile.isEmpty()) {
        Card* card = exhaustPile.takeLast();
        player->ADD_TO_HAND(card);
    }
}

Card* Exhume::upgrade() {
    Exhume* upgraded = new Exhume(*this);
    upgraded->is_Upgrade = true;
    upgraded->description = "Put a card from exhaust pile into hand - Exhaust.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Exhume::clone() const {
    return new Exhume(*this);
}