#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QPixmap>
#include <QPainter>
#include "player.h"
#include "buff_debuff.h"

struct Intent {
    enum Type {
        ATTACK,
        DEFEND,
        DEBUFF,
        BUFF,
        MIXED
    };
    Type type;
    int value;
    QString description;
};

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Enemy(const QString& name, int hp, QGraphicsItem *parent = nullptr);
    Enemy(const Enemy& other);
    virtual ~Enemy() = default;

    QString getName() const { return name; }
    int getHP() const { return currentHP; }
    int getMaxHP() const { return maxHP; }
    int getBlock() const { return block; }
    void setBlock(int amount) { block = qMax(0, amount); }

    virtual void takeDamage(int amount);
    virtual void gainBlock(int amount);
    void heal(int amount);

    void ADD_BUFF(BuffType type, int value, int turns = -1) { buffManager.add(type, value, turns); }
    void REMOVE_BUFF(BuffType type) { buffManager.remove(type); }
    bool HAS_BUFF(BuffType type) const { return buffManager.has(type); }
    int GET_BUFF_VALUE(BuffType type) const { return buffManager.getTotalValue(type); }
    QString GET_BUFFS_DESCRIPTION() const { return buffManager.getDescription(); }

    int APPLY_VULNERABLE_TO_DAMAGE(int damage) const { return buffManager.applyVulnerableToDamage(damage); }
    int APPLY_WEAK_TO_DAMAGE(int damage) const { return buffManager.applyWeakToDamage(damage); }
    int APPLY_FRAIL_TO_BLOCK(int block) const { return buffManager.applyFrailToBlock(block); }

    virtual Intent getNextIntent() = 0;
    virtual void executeIntent(player& player) = 0;
    virtual void startTurn();
    virtual void endTurn();

    virtual void loadImage(const QString& path);
    virtual QString getDefaultImagePath() const;

signals:
    void hpChanged(int newHP, int maxHP);
    void blockChanged(int newBlock);
    void intentChanged(const Intent& intent);
    void enemyDied(Enemy* enemy);

protected:
    QString name;
    int maxHP;
    int currentHP;
    int block;
    BuffDebuffManager buffManager;
    Intent currentIntent;
};

#endif // ENEMY_H