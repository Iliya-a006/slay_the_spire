#ifndef BUFF_DEBUFF_H
#define BUFF_DEBUFF_H

#include <QVector>
#include <QString>

enum BuffType {
    Strength = 0,
    Dexterity = 1,
    Metallicize = 2,

    Vulnerable = 10,
    Weak = 11,
    Frail = 12
};

struct BuffDebuff {
    BuffType type;
    int value;
    int turnsLeft;

    BuffDebuff(BuffType t = Strength, int v = 0, int turns = -1)
        : type(t), value(v), turnsLeft(turns) {}
};

class BuffDebuffManager
{
public:
    BuffDebuffManager() = default;
    ~BuffDebuffManager() = default;


    void add(BuffType type, int value, int turns = -1);
    void remove(BuffType type);
    bool has(BuffType type) const;
    int getValue(BuffType type) const;
    int getTotalValue(BuffType type) const;
    void clearAll();
    void decreaseTurns();
    QString getDescription() const;


    int applyVulnerableToDamage(int damage) const;
    int applyWeakToDamage(int damage) const;
    int applyFrailToBlock(int block) const;
    void applyMetallicizeAtEndOfTurn(int& block);

private:
    QVector<BuffDebuff> buffs;
};

#endif // BUFF_DEBUFF_H