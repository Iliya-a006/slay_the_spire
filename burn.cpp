#include "burn.h"
#include"player.h"
#include"enemy.h"

Burn::Burn(QGraphicsItem *parent) : StatusCard(parent),burnDamage(2) {
    ID = 103;
    name = "Burn";
    energy_cost = -1;
    rarity = COMMON;
    description = "Unplayable.\nAt the end of your turn,\ntake "+QString::number(2)+" damage.";
    is_Exhaust = false;
    is_Ethereal = true;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Burn::Burn(const Burn& other) : StatusCard(other) {
    burnDamage = other.burnDamage;
}

void Burn::setBurnDamage(int dmg) {
    burnDamage = dmg;
    description = "Unplayable. At the end of your turn, take " + QString::number(burnDamage) + " damage.";
}
void Burn::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(player);
    Q_UNUSED(enemies);
}

Card* Burn::upgrade() {
    Burn* upgraded = new Burn(*this);
    upgraded->is_Upgrade = true;
    upgraded->burnDamage=4;
    upgraded->description="Unplayable.\nAt the end of your turn,\ntake "+QString::number(4)+" damage.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Burn::clone() const {
    return new Burn(*this);
}