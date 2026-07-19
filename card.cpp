//#include "card.h"
#include "player.h"
Card::Card(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
    ID(-1),
    name(""),
    energy_cost(0),
    type(Card_Type::ATTACK),
    rarity(Card_Rarity::BASIC),
    is_Exhaust(false),
    is_Ethereal(false),
    is_Retain(false),
    is_Upgrade(false),
    description(""),
    damage(0),
    hovered(false),
    playeable(false){
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setScale(0.8);

}
int Card::getCurrentCost(const player* player) const {
    Q_UNUSED(player);
    return energy_cost;
}
bool Card::canPlay(player* player) const {
    if (type == STATUS || type == CURSE) return false;
    if (!player) return false;
    int cost = getCurrentCost(player);
    return player->GETER_SETEE_ENERGY() >= cost;
}
// void Card::Load_Card_Image(bool upgraded){
//     QPixmap pixmap=
// }