#include "cultist.h"
#include <QPixmap>

Cultist::Cultist(QGraphicsItem *parent) : NormalEnemy("Cultist", 0, parent) {
    int hp = 48 + (rand() % 7);
    maxHP = hp;
    currentHP = hp;

    m_imagePath = ":/normalenemies/NORMAL_ENEMIES/cultist.png";
    loadImage();
}

Cultist::Cultist(const Cultist& other) : NormalEnemy(other) {
    turn = other.turn;
    m_imagePath = other.m_imagePath;
    setPixmap(other.pixmap());
}

Intent Cultist::getNextIntent() {
    ++turn;
    if (turn == 1) {
        currentIntent = {Intent::BUFF, 3};
    } else {
        int dmg = 6 + buffManager.getTotalValue(Strength);
        currentIntent = {Intent::ATTACK, dmg};
    }
    emit intentChanged(currentIntent);
    return currentIntent;
}

void Cultist::executeIntent(player& player) {
    if (turn == 1) {
        buffManager.add(Strength, 3);
    } else {
        int dmg = 6 + buffManager.getTotalValue(Strength);
        player.TAKE_DAMAGE(dmg);
    }
}