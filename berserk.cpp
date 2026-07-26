#include"berserk.h"
#include"player.h"
#include"enemy.h"
#include"buff_debuff.h"

Berserk::Berserk(QGraphicsItem *parent) : PowerCard(parent) {
    ID = 28;
    name = "Berserk";
    energy_cost = 0;
    rarity = RARE;
    description = "Gain 2 Vulnerable - At the start of your turn get 1 extra Energy.";
    is_Exhaust = true;
    is_Ethereal = false;
    is_Retain = false;
    is_Upgrade = false;
    Load_Card_Image();
}

Berserk::Berserk(const Berserk& other) : PowerCard(other) {}

void Berserk::play(player* player, QList<Enemy*>& enemies) {
    Q_UNUSED(enemies);
    applyPower(player);
}

void Berserk::applyPower(player* player) {
    player->ADD_BUFF(Vulnerable, 2, 2);
    player->ADD_BUFF(BuffType::Berserk, 1, -1);
}

Card* Berserk::upgrade() {
    Berserk* upgraded = new Berserk(*this);
    upgraded->is_Upgrade = true;
    upgraded->description = "Gain 2 Vulnerable - At the start of your turn get 1 extra Energy.";
    upgraded->Load_Card_Image(true);
    return upgraded;
}

Card* Berserk::clone() const {
    return new Berserk(*this);
}