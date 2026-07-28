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
    buffManager(other.buffManager),
    m_imagePath(other.m_imagePath)
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

void Enemy::loadImage() {
    if (m_imagePath.isEmpty()) {
        loadFallbackImage();
        return;
    }

    QPixmap pixmap(m_imagePath);
    if (!pixmap.isNull()) {
        setPixmap(pixmap);
        setScale(0.8);
    } else {
        loadFallbackImage();
    }
}

void Enemy::loadFallbackImage() {
    QPixmap fallback(100, 100);
    fallback.fill(QColor(200, 50, 50));
    QPainter painter(&fallback);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(fallback.rect(), Qt::AlignCenter, name);
    setPixmap(fallback);
    setScale(0.8);
}