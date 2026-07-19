#include "strike.h"
#include"player.h"
#include"enemy.h"
Strike::Strike(QGraphicsItem *parent) : Attack_Cards(parent) {
    ID = 1;
    name = "Strike";
    energy_cost = 1;
    rarity = COMMON;
    damage = 6;
    description = "Deal 6 damage.";
    is_Exhaust = false;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}
Strike::Strike(const Strike& other):Attack_Cards(other){;}
void Strike::play(player* player, QList<Enemy*>& enemies) {
    int dmg = calculate_damage(player);
    applay_damage(player, enemies, dmg);
}

Card* Strike::upgrade() {
    Strike* upgraded = new Strike(*this);
    upgraded->damage += 3;
    upgraded->is_Upgrade = true;
    upgraded->description = "Deal 9 damage.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Strike::clone() const {
    return new Strike(*this);
}