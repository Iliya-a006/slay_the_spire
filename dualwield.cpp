#include "dualwield.h"
#include "player.h"
#include "enemy.h"
#include <QRandomGenerator>

DualWield::DualWield(QGraphicsItem *parent) : SkillCard(parent) {
    ID = 16;
    name = "Dual Wield";
    energy_cost = 1;
    rarity = UNCOMMON;
    block = 0;
    description = "Choose an Attack or\nPower card. Add a copy\nof that card into your hand.";
    is_Exhaust = false;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

void DualWield::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    QVector<Card*>& hand = player->GETER_HAND();
    if (hand.isEmpty()) return;
    QVector<Card*> validCards;
    for (Card* card : hand) {
        if (card->GETER_TYPE() == ATTACK || card->GETER_TYPE() == POWER) {
            validCards.append(card);
        }
    }
    if (validCards.isEmpty()) return;
    int randomIndex = QRandomGenerator::global()->bounded(validCards.size());
    Card* selectedCard = validCards[randomIndex];
    int copyCount = is_Upgrade ? 2 : 1;
    for (int i = 0; i < copyCount; ++i) {
        Card* clone = selectedCard->clone();
        if (!player->IS_HAND_FULL()) {
            player->ADD_TO_HAND(clone);
        } else {
            delete clone;
            break;
        }
    }
}

Card* DualWield::upgrade() {
    DualWield* upgraded = new DualWield(*this);
    upgraded->is_Upgrade = true;
    upgraded->description = "Choose an Attack or\nPower card. Add 2 copy\nof that card into your hand.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* DualWield::clone() const {
    return new DualWield(*this);
}