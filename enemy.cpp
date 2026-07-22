#include "enemy.h"
#include <QPixmap>

Enemy::Enemy(const QString& name, int hp, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
    name(name),
    maxHP(hp),
    currentHP(hp),
    block(0)
{
    setAcceptHoverEvents(true);
    setScale(0.8);
}

Enemy::Enemy(const Enemy& other)
    : QGraphicsPixmapItem(other.parentItem()),
    name(other.name),
    maxHP(other.maxHP),
    currentHP(other.currentHP),
    block(other.block),
    buffManager(other.buffManager)
{
    setAcceptHoverEvents(true);
    setScale(0.8);
    setPixmap(other.pixmap());
}

void Enemy::takeDamage(int amount) {
    int remaining = amount - block;
    if (remaining > 0) {
        currentHP = qMax(0, currentHP - remaining);
        block = 0;
    } else {
        block -= amount;
    }
    emit hpChanged(currentHP, maxHP);
    if (currentHP <= 0) {
        emit enemyDied(this);
    }
}

void Enemy::gainBlock(int amount) {
    block += amount;
    emit blockChanged(block);
}

void Enemy::heal(int amount) {
    currentHP = qMin(maxHP, currentHP + amount);
    emit hpChanged(currentHP, maxHP);
}

void Enemy::startTurn() {
    buffManager.decreaseTurns();

    buffManager.applyMetallicizeAtEndOfTurn(block);
    emit blockChanged(block);
}

void Enemy::endTurn() {
    buffManager.applyMetallicizeAtEndOfTurn(block);
    emit blockChanged(block);
}

void Enemy::loadImage(const QString& path) {
    QPixmap pixmap(path);
    if (!pixmap.isNull()) {
        setPixmap(pixmap);
        setScale(0.8);
    }
}

QString Enemy::getDefaultImagePath() const {
    QString formattedName = name.toLower().replace(" ", "_");
    return QString(":/enemies/%1.jpg").arg(formattedName);
}