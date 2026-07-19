#include "feed.h"
#include "player.h"
#include"enemy.h"
Feed::Feed(QGraphicsItem *parent) : Attack_Cards(parent) {
    ID = 10;
    name = "Feed";
    energy_cost = 1;
    rarity = RARE;
    damage = 10;
    description = "Deal 10 damage. If fatal, raise max HP by 3. Exhaust.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Feed::Feed(const Feed& other) : Attack_Cards(other) {}

void Feed::play(player* player, QList<Enemy*>& enemies) {
    if (enemies.isEmpty()) return;
    Enemy* target = enemies.first();
    int hpBefore = target->getHP();
    int dmg = calculate_damage(player);
    target->takeDamage(dmg);
    if (target->getHP() <= 0 && hpBefore > 0) {
        player->INCREASE_MAXHP(3);
    }
}

Card* Feed::upgrade() {
    Feed* upgraded = new Feed(*this);
    upgraded->damage += 4;
    upgraded->is_Upgrade = true;
    upgraded->description = "Deal 14 damage. If fatal, raise max HP by 4. Exhaust.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Feed::clone() const {
    return new Feed(*this);
}