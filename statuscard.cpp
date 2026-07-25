#include "statuscard.h"

StatusCard::StatusCard(QGraphicsItem *parent) : Card(parent) {
    type = STATUS;
    energy_cost = -1;
}

StatusCard::StatusCard(const StatusCard& other) : Card(other) {}

bool StatusCard::canPlay(player* player) const {
    Q_UNUSED(player);
    return false;
}

QString StatusCard::getCardTypeFolder() const {
    return "STATUS_CARDS";
}