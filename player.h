#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QVector>
#include <QDataStream>
#include "card.h"
#include <QList>
#include <QPixmap>

class player
{
public:
    explicit player();
    QString getName(){return username;}
    int getMapID(){return mapID;}
    void setMapID(int id){mapID = id;}
    int& GETER_SETEE_ENERGY(){return energy;}

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
    void ADD_BLOCK(int amount) { block += amount; }
    void ADD_STRENGtH(int amount) { strength += amount; }
    void ADD_DEXTERITY(int amount) { dexterity += amount; }
    void SPEND_ENERGY(int amount) { energy = qMax(0, energy - amount); }
    void TAKE_DAMAGE(int damage);
    void HEAL(int amount) { HP = qMin(maxHP, HP + amount); }
    void RESETCOMBATSTATS() { block = 0; strength = 0; unblockedDamageTaken = 0; }

    void ADD_TO_HAND(Card* card);
    void REMOVE_FROM_HAND(Card* card);
    bool IS_HAND_FULL() const { return hand.size() >= 10; }
    // void ADD_CARD_TO_DEK(int IDCard){cards.append(IDCard);}
    // void REMOVE_CARD_FROM_DEK(int IDCard){cards.removeAll(IDCard);}
    // QVector<int>GET_IDCARDS()const{return cards;}

    void ADD_TO_DRAWPILE(Card* card);
    void ADD_TO_DISCARDPILE(Card* card);
    void ADD_TO_EXHAUSTPILE(Card* card);
    void SHUFFLE_DRAWPILE();
    void SHUFFLE_DISCARDPILE();

    void START_TURN();
    void END_TURN();
    void DRAW_CARD(int count);

    QPixmap GETER_AVATAR() const { return avatar; }
    void SETER_AVATAR(const QPixmap& pix) { avatar = pix; }
    void SETER_AVATAR_PATH(const QString& path) { avatar.load(path); }
    void LOAD_DEFAUL_TAVATAR();
private:
    static player* m_instance;

    QPixmap avatar;
    QString username;
    QString password;
    int gold;
    int Act;
    int floor;
    int maxHP;
    int HP;
    int energy;
    int mapID = -1;
    int block=0;
    int strength=0;
    int dexterity=0;
    int unblockedDamageTaken=0;//for blood for blood
    bool barricadeActive;//for cards

    QVector<Card*> hand;
    QVector<Card*> drawPile;
    QVector<Card*> discardPile;
    QVector<Card*> exhaustPile;
    //QVector<int> cards;
    QVector<int> buff_debuffs;
    QVector<int> potions;
    QVector<int> relics;
public:
    void writeToStream(QDataStream &out) const;
    void readFromStream(QDataStream& in);
    static bool appendPlayer(QString name, QString pass);
    static bool findPlayer(QString name, QString pass);
    static void saveFile();
};

#endif // PLAYER_H
