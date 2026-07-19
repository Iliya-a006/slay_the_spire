#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QWidget>
#include <QVector>
#include <QDataStream>
#include "card.h"
#include "buff_debuff.h"
#include <QList>
#include <QPixmap>


class player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit player(QGraphicsItem *parent = nullptr);
    player(const player& other);
    ~player() = default;

    player& operator=(const player& other);

    QString getName() { return username; }
    int getMapID() { return mapID; }
    void setMapID(int id) { mapID = id; }
    int& GETER_SETER_ENERGY() { return energy; }

    static player* instance();

    int GETER_HP() const { return HP; }
    int GETER_MAXHP() const { return maxHP; }
    int GETER_ENERGY() const { return energy; }
    int GETER_GOLD() const { return gold; }
    int GETER_BLOCK() const { return block; }
    int GETER_STRENGtH() const { return strength; }
    int GETER_DEXTERITY() const { return dexterity; }
    int GETER_UNBLOCKEDDAMAGETAKEN() const { return unblockedDamageTaken; }

    QVector<Card*>& GETٍER_HAND() { return hand; }
    QVector<Card*>& GETٍER_DRAWPILE() { return drawPile; }
    QVector<Card*>& GETٍER_DISCARDPILE() { return discardPile; }
    QVector<Card*>& GETٍER_EXHAUSTPILE() { return exhaustPile; }

    void SETٍER_BLOCK(int amount) { block = qMax(0, amount); }
    void SETٍER_STRENGtH(int amount) { strength = amount; }
    void SETٍER_DEXTERITY(int amount) { dexterity = amount; }

    void ADD_BLOCK(int amount);
    void ADD_STRENGtH(int amount) { strength += amount; }
    void ADD_DEXTERITY(int amount) { dexterity += amount; }
    void SPEND_ENERGY(int amount) { energy = qMax(0, energy - amount); }
    void TAKE_DAMAGE(int damage);
    void HEAL(int amount) { HP = qMin(maxHP, HP + amount); }
    void RESETCOMBATSTATS() { block = 0; strength = 0; unblockedDamageTaken = 0; }

    void ADD_TO_HAND(Card* card);
    void REMOVE_FROM_HAND(Card* card);
    bool IS_HAND_FULL() const { return hand.size() >= 10; }

    void LOSE_HP(int amount);
    void INCREASE_MAXHP(int amount);
    void SET_MAXHP(int newMax);

    void ADD_BUFF(BuffType type, int value, int turns = -1) { buffManager.add(type, value, turns); }
    void REMOVE_BUFF(BuffType type) { buffManager.remove(type); }
    bool HAS_BUFF(BuffType type) const { return buffManager.has(type); }
    int GET_BUFF_VALUE(BuffType type) const { return buffManager.getTotalValue(type); }
    QString GET_BUFFS_DESCRIPTION() const { return buffManager.getDescription(); }

    int APPLY_VULNERABLE_TO_DAMAGE(int damage) const { return buffManager.applyVulnerableToDamage(damage); }
    int APPLY_WEAK_TO_DAMAGE(int damage) const { return buffManager.applyWeakToDamage(damage); }
    int APPLY_FRAIL_TO_BLOCK(int block) const { return buffManager.applyFrailToBlock(block); }

    void ADD_TO_DRAWPILE(Card* card);
    void ADD_TO_DISCARDPILE(Card* card);
    void ADD_TO_EXHAUSTPILE(Card* card);
    void SHUFFLE_DRAWPILE();
    void SHUFFLE_DISCARDPILE();


    void START_TURN();
    void END_TURN();
    void DRAW_CARD(int count);

    void loadAvatar(const QString& path);
    void loadDefaultAvatar();

signals:
    void hpChanged(int newHP, int maxHP);
    void blockChanged(int newBlock);
    void energyChanged(int newEnergy);
    void handUpdated();

private:
    static player* m_instance;

    QString username;
    QString password;
    QString oldUsername;
    QString oldPassword;
    int gold;
    int Act;
    int floor;

    int maxHP;
    int HP;
    int energy;
    int mapID = -1;
    int block = 0;
    int strength = 0;
    int dexterity = 0;
    int unblockedDamageTaken = 0;
    bool barricadeActive = false;

    QVector<Card*> hand;
    QVector<Card*> drawPile;
    QVector<Card*> discardPile;
    QVector<Card*> exhaustPile;

    QVector<int> potions;
    QVector<int> relics;

    BuffDebuffManager buffManager;

public:
    void writeToStream(QDataStream &out) const;
    void readFromStream(QDataStream& in);
    static bool appendPlayer(QString name, QString pass);
    static bool findPlayer(QString name, QString pass);
    static void saveFile();
};

#endif // PLAYER_H