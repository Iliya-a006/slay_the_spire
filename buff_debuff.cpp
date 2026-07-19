#include "buff_debuff.h"

void BuffDebuffManager::add(BuffType type, int value, int turns) {
    for (auto& b : buffs) {
        if (b.type == type) {
            b.value += value;
            if (turns == -1 || b.turnsLeft == -1) {
                b.turnsLeft = -1;
            } else {
                b.turnsLeft = qMax(b.turnsLeft, turns);
            }
            return;
        }
    }
    buffs.append(BuffDebuff(type, value, turns));
}

void BuffDebuffManager::remove(BuffType type) {
    for (int i = buffs.size() - 1; i >= 0; --i) {
        if (buffs[i].type == type) {
            buffs.removeAt(i);
            break;
        }
    }
}

bool BuffDebuffManager::has(BuffType type) const {
    for (const auto& b : buffs) {
        if (b.type == type) return true;
    }
    return false;
}

int BuffDebuffManager::getValue(BuffType type) const {
    for (const auto& b : buffs) {
        if (b.type == type) return b.value;
    }
    return 0;
}

int BuffDebuffManager::getTotalValue(BuffType type) const {
    int total = 0;
    for (const auto& b : buffs) {
        if (b.type == type) total += b.value;
    }
    return total;
}

void BuffDebuffManager::clearAll() {
    buffs.clear();
}

void BuffDebuffManager::decreaseTurns() {
    for (int i = buffs.size() - 1; i >= 0; --i) {
        if (buffs[i].turnsLeft > 0) {
            buffs[i].turnsLeft--;
            if (buffs[i].turnsLeft == 0) {
                buffs.removeAt(i);
            }
        }
    }
}

QString BuffDebuffManager::getDescription() const {
    if (buffs.isEmpty()) return "None";

    QStringList desc;
    for (const auto& b : buffs) {
        QString name;
        switch (b.type) {
        case Strength: name = "Strength"; break;
        case Dexterity: name = "Dexterity"; break;
        case Metallicize: name = "Metallicize"; break;
        case Vulnerable: name = "Vulnerable"; break;
        case Weak: name = "Weak"; break;
        case Frail: name = "Frail"; break;
        default: name = "Unknown"; break;
        }
        desc.append(QString("%1: %2").arg(name).arg(b.value));
    }
    return desc.join(", ");
}


int BuffDebuffManager::applyVulnerableToDamage(int damage) const {
    if (has(Vulnerable)) {
        int val = getTotalValue(Vulnerable);
        if (val > 0) {
            damage = damage * (100 + 50 * val) / 100;
        }
    }
    return damage;
}


int BuffDebuffManager::applyWeakToDamage(int damage) const {
    if (has(Weak)) {
        int val = getTotalValue(Weak);
        if (val > 0) {
            damage = damage * (100 - 50 * val) / 100;
            if (damage < 0) damage = 0;
        }
    }
    return damage;
}

int BuffDebuffManager::applyFrailToBlock(int block) const {
    if (has(Frail)) {
        int val = getTotalValue(Frail);
        if (val > 0) {
            block = block * (100 - 25 * val) / 100;
            if (block < 0) block = 0;
        }
    }
    return block;
}

void BuffDebuffManager::applyMetallicizeAtEndOfTurn(int& block) {
    if (has(Metallicize)) {
        int metalValue = getTotalValue(Metallicize);
        block += metalValue;
    }
}