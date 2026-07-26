#include "metallicize.h"
#include"player.h"
#include"enemy.h"
#include"buff_debuff.h"
Metallicize::Metallicize(QGraphicsItem *parent) : PowerCard(parent) {
    ID = 22;
    name = "Metallicize";
    energy_cost = 1;
    rarity = UNCOMMON;
    description = "At the end of your turn,\ngain "+QString::number(3)+" Block.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Metallicize::Metallicize(const Metallicize& other) : PowerCard(other) {}

void Metallicize::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    applyPower(player);
}

void Metallicize::applyPower(player* player) {

      if (is_Upgrade) {
            player->ADD_BUFF(BuffType::Metallicize, 5, -1);
     } else {
            player->ADD_BUFF(BuffType::Metallicize, 3, -1);
    }

}

Card* Metallicize::upgrade() {
    Metallicize* upgraded = new Metallicize(*this);
    upgraded->is_Upgrade = true;
    upgraded->description = "At the end of your turn,\ngain "+QString::number(4)+" Block.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Metallicize::clone() const {
    return new Metallicize(*this);
}