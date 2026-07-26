#ifndef BUFF_DEBUFF_H
#define BUFF_DEBUFF_H

#include <QVector>
#include <QString>

enum BuffType {
    Strength = 0,
    Dexterity = 1,
    Metallicize = 2,
    Barricade = 3,
    FeelNoPain = 4,
    DarkEmbrace = 5,
    Berserk = 6,
    Brutality = 7,
    DemonForm = 8,
    Incantation = 9,
    Enrage = 10,

    Vulnerable = 20,
    Weak = 21,
    Frail = 22,
    Entangle = 23,
    Burn = 24,
    Regret = 25
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

    void applyEndOfTurnEffects(int& block, int& hp, int handSize);

    void applyStartOfTurnEffects(int& energy, int& hp);

private:
    QVector<BuffDebuff> buffs;
};

#endif // BUFF_DEBUFF_H