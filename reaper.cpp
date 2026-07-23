#include "reaper.h"
#include "player.h"
#include"enemy.h"
Reaper::Reaper(QGraphicsItem *parent) : Attack_Cards(parent) {
    ID = 9;
    name = "Reaper";
    energy_cost = 2;
    rarity = RARE;
    damage = 4;
    description = "Deal " + QString::number(damage) +
                  " damage to ALL enemies.\nHeal HP equal to unblocked damage.\nExhaust.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Reaper::Reaper(const Reaper& other) : Attack_Cards(other) {}

void Reaper::play(player* player, QList<Enemy*>& enemies) {
    int dmg = calculate_damage(player);
    int totalUnblocked = 0;
    for (Enemy* e : enemies) {
        int hpBefore = e->getHP();
        e->takeDamage(dmg);
        int hpAfter = e->getHP();
        totalUnblocked += (hpBefore - hpAfter);
    }
    player->HEAL(totalUnblocked);
}

Card* Reaper::upgrade() {
    Reaper* upgraded = new Reaper(*this);
    upgraded->damage += 3;
    upgraded->is_Upgrade = true;
    upgraded->description = "Deal " + QString::number(upgraded->damage) +
                            " damage to ALL enemies.\nHeal HP equal to unblocked damage.\nExhaust.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Reaper::clone() const {
    return new Reaper(*this);
}