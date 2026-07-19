#include "attack_cards.h"
#include "player.h"
#include "enemy.h"
Attack_Cards::Attack_Cards(QGraphicsItem *parent):Card(parent) {
    type=Card_Type::ATTACK;
}
Attack_Cards::Attack_Cards(const Attack_Cards& other) : Card(other) {

}

int Attack_Cards::calculate_damage(const player* player)const{
    int dmg=damage+player->GETER_STRENGtH();
    return dmg;
}


void Attack_Cards::applay_damage(player* player,QList<Enemy*>&enemies,int damage){
    for (Enemy* e : enemies) {
        e->takeDamage(damage);
    }
}