#include "powercard.h"

PowerCard::PowerCard(QGraphicsItem *parent) : Card(parent) {
    type = POWER;
    is_Exhaust = true;
}

PowerCard::PowerCard(const PowerCard& other) : Card(other) {}

QString PowerCard::getCardTypeFolder() const {
    return "POWER_CARDS";
}