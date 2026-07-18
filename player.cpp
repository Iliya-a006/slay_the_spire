#include "player.h"
#include <QFile>
#include <QDataStream>
#include <algorithm>
#include <random>
player::player()
{
    gold = 0;
    Act = 1;
    floor = 0;
    maxHP = 80;
    HP = maxHP;
    energy=3;
    mapID = -1;
    block=0;
    strength=0;
    dexterity=0;
    unblockedDamageTaken=0;
    barricadeActive=false;
    // initializeDeck();
    //cards.push_back(...);
}

player* player::m_instance = nullptr;
player* player::instance()
{
    if (!m_instance)
        m_instance = new player;
    return m_instance;
}

void player::writeToStream(QDataStream &out) const
{
    out << username << password << gold << Act << floor << maxHP << HP << mapID;
    out << /*cards <<*/ /*buff_debuffs << */potions << relics;
}

void player::readFromStream(QDataStream &in)
{
    in >> username >> password >> gold >> Act >> floor >> maxHP >> HP >> mapID;
    in >> /*cards >>*/ /*buff_debuffs >> */potions >> relics;
}

bool player::appendPlayer(QString name, QString pass)
{
    instance()->username = name;
    instance()->password = pass;
    QFile file("players.bin");
    if (!file.open(QIODevice::Append))
        return false;
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_5);
    instance()->writeToStream(out);
    file.close();
    return true;
}

bool player::findPlayer(QString name, QString pass)
{
    QFile file("players.bin");
    if (!file.open(QIODevice::ReadOnly))
        return false;
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_5);

    player* p = new player;
    while(!in.atEnd()){
        p->readFromStream(in);
        if (p->username == name && p->password == pass){
            delete instance();
            m_instance = p;
            file.close();
            return true;
        }
    }
    delete p;
    file.close();
    return false;
}

void player::saveFile()
{
    QVector<player> players;
    player p;

    QFile file("players.bin");
    if (!file.open(QIODevice::ReadOnly))
        return;
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_5);
    while(!in.atEnd()){
        p.readFromStream(in);
        if (p.username == m_instance->username && p.password == m_instance->password)
            p = *m_instance;
        players.push_back(p);
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly))
        return;
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_5);
    for (int i=0; i<players.length(); ++i)
        players[i].writeToStream(out);
    file.close();
}


void player::TAKE_DAMAGE(int damage){
    int reminder_of_damage=damage-block;
    if(reminder_of_damage>0){
        HP=qMax(0,HP-reminder_of_damage);
        unblockedDamageTaken+=reminder_of_damage;
        block=0;
        return;
    }else{
        block-=damage;
        return;
    }
}

void player::ADD_TO_HAND(Card* card){
    if(card&&hand.size()<10){
        hand.push_back(card);
    }
}

void player::REMOVE_FROM_HAND(Card* card){
    hand.removeAll(card);
}

void player::ADD_TO_DISCARDPILE(Card* card){
    if(card!=NULL){
        discardPile.append(card);
    }
}

void player::ADD_TO_DRAWPILE(Card* card){
    if(card!=NULL){
        drawPile.append(card);
    }
}
void player::ADD_TO_EXHAUSTPILE(Card* card ){
    if(card!=NULL){
        exhaustPile.append(card);
    }
}

void player::SHUFFLE_DRAWPILE(){
    std::random_device rand;
    std::mt19937 g(rand());
    std::shuffle(drawPile.begin(),drawPile.end(),g);
}
void player::SHUFFLE_DISCARDPILE(){
    std::random_device rand;
    std::mt19937 g(rand());
    std::shuffle(discardPile.begin(),discardPile.end(),g);
}

void player::START_TURN()
{
    energy = 3;
    DRAW_CARD(5);
    if (barricadeActive==false) {
        block = 0;
    }
}

void player::DRAW_CARD(int count){
    int draw=0;
    while(draw<count){
        if(drawPile.isEmpty()){
            if(discardPile.isEmpty()){
                break;
            }
            drawPile=discardPile;
            discardPile.clear();
            SHUFFLE_DRAWPILE();
        }
        if(hand.size()>=10){
            break;
        }
        Card* card=drawPile.takeLast();
        hand.append(card);
        draw++;
    }
}

void player::END_TURN(){
    energy=0;
    QVector<Card*> retiancard;
    QVector<Card*> discard;
    QVector<Card*> exhaust;

    for(Card* card:hand){
        if(card->GETER_SETER_RETAIN()){
            retiancard.append(card);
        }else if(card->GETER_SETER_Exhaust()){
            exhaust.append(card);
        }else{
            discard.append(card);
        }
    }
    hand.clear();
    hand=retiancard;

    for(Card* card:discard){
        discardPile.append(card);
    }
    for(Card* card:exhaust){
        exhaustPile.append(card);
    }
    if(barricadeActive==false){
        block=0;
    }
}

void player::LOAD_DEFAUL_TAVATAR(){
    if(avatar.load("")==true){
        ;
    }else{

    }
}