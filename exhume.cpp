#include "exhume.h"
#include "player.h"
#include "enemy.h"
#include <random>
Exhume::Exhume(QGraphicsItem *parent) : SkillCard(parent) {
    ID = 12;
    name = "Exhume";
    energy_cost = 1;
    rarity = RARE;
    block = 0;
    description = "Put a card from your\nexhaust pile into your\nhand.\nExhaust.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Exhume::Exhume(const Exhume& other) : SkillCard(other) {}

void Exhume::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    QVector<Card*>& exhaustPile = player->GETER_EXHAUSTPILE();
    if (exhaustPile.isEmpty()) return;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(exhaustPile.begin(), exhaustPile.end(), g);
    Card* card = exhaustPile.takeLast();
    if (!player->IS_HAND_FULL()) {
        player->ADD_TO_HAND(card);
    } else {
        player->ADD_TO_DISCARDPILE(card);
    }
}

Card* Exhume::upgrade() {
    Exhume* upgraded = new Exhume(*this);
    upgraded->is_Upgrade = true;
    upgraded->energy_cost = 0;
    upgraded->description = "Put a card from your\nexhaust pile into your\nhand.\nExhaust.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Exhume::clone() const {
    return new Exhume(*this);
}