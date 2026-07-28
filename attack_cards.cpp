#include "attack_cards.h"
#include "player.h"
#include "enemy.h"

Attack_Cards::Attack_Cards(QGraphicsItem *parent) : Card(parent) {
    type = Card_Type::ATTACK;
}

Attack_Cards::Attack_Cards(const Attack_Cards& other) : Card(other) {

}

int Attack_Cards::calculate_damage(const player* player) const {
    int dmg = damage + player->GETER_STRENGtH();
    return dmg;
}

void Attack_Cards::applay_damage(player* player, QList<Enemy*>& enemies, int damage) {
    Q_UNUSED(player);
    for (Enemy* e : enemies) {
        if (e) {
            e->takeDamage(damage);
        }
    }
}

QString Attack_Cards::getCardTypeFolder() const {
    return "ATTACK_CARDS";
}