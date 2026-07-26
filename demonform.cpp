#include "demonform.h"
#include"player.h"
#include"enemy.h"
#include"buff_debuff.h"
DemonForm::DemonForm(QGraphicsItem *parent) : PowerCard(parent) {
    ID = 23;
    name = "Demon Form";
    energy_cost = 3;
    rarity = RARE;
    description = "At the start of your turn gain 3 Strength.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

DemonForm::DemonForm(const DemonForm& other) : PowerCard(other) {}

void DemonForm::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    applyPower(player);
}

void DemonForm::applyPower(player* player) {
    player->ADD_BUFF(BuffType::DemonForm, 3, -1);
}

Card* DemonForm::upgrade() {
    DemonForm* upgraded = new DemonForm(*this);
    upgraded->energy_cost = 2;
    upgraded->is_Upgrade = true;
    upgraded->description = "At the start of your turn gain 3 Strength.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* DemonForm::clone() const {
    return new DemonForm(*this);
}