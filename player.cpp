#include "player.h"
#include <QFile>
#include <QDataStream>
#include <algorithm>
#include <random>
#include <QPainter>
#include "strike.h"
#include "twinstrike.h"
#include "bloodforblood.h"
#include "hemokinesis.h"
#include "carnage.h"
#include "whirlwind.h"
#include "bludgeon.h"
#include "immolate.h"
#include "reaper.h"
#include "feed.h"

player::player(QGraphicsItem *parent)
    : QObject(nullptr),
    QGraphicsPixmapItem(parent)
{
    gold = 0;
    Act = 1;
    floor = 0;
    maxHP = 80;
    HP = maxHP;
    energy = 3;
    mapID = -1;
    block = 0;
    strength = 0;
    dexterity = 0;
    unblockedDamageTaken = 0;
    barricadeActive = false;

    setAcceptHoverEvents(true);
    setScale(0.8);
    loadDefaultAvatar();
    initializeDeck();
}

player::player(const player& other)
    : QObject(nullptr),
    QGraphicsPixmapItem(other.parentItem())
{

    username = other.username;
    password = other.password;
    gold = other.gold;
    Act = other.Act;
    floor = other.floor;

    maxHP = other.maxHP;
    HP = other.HP;
    energy = other.energy;
    mapID = other.mapID;
    block = other.block;
    strength = other.strength;
    dexterity = other.dexterity;
    unblockedDamageTaken = other.unblockedDamageTaken;
    barricadeActive = other.barricadeActive;

    hand = other.hand;
    drawPile = other.drawPile;
    discardPile = other.discardPile;
    exhaustPile = other.exhaustPile;

    potions = other.potions;
    relics = other.relics;

    buffManager = other.buffManager;

    setPixmap(other.pixmap());
    setScale(0.8);
}

player& player::operator=(const player& other)
{
    if (this == &other) {
        return *this;
    }


    username = other.username;
    password = other.password;
    gold = other.gold;
    Act = other.Act;
    floor = other.floor;

    maxHP = other.maxHP;
    HP = other.HP;
    energy = other.energy;
    mapID = other.mapID;
    block = other.block;
    strength = other.strength;
    dexterity = other.dexterity;
    unblockedDamageTaken = other.unblockedDamageTaken;
    barricadeActive = other.barricadeActive;

    hand = other.hand;
    drawPile = other.drawPile;
    discardPile = other.discardPile;
    exhaustPile = other.exhaustPile;

    potions = other.potions;
    relics = other.relics;

    buffManager = other.buffManager;

    setPixmap(other.pixmap());
    setScale(0.8);

    return *this;
}

player* player::m_instance = nullptr;

player* player::instance()
{
    if (!m_instance)
        m_instance = new player;
    return m_instance;
}

void player::loadAvatar(const QString& path) {
    QPixmap pixmap(path);
    if (!pixmap.isNull()) {
        setPixmap(pixmap);
        setScale(0.8);
    }
}

void player::loadDefaultAvatar() {
    QPixmap pixmap(":/avartar/images/Ironclad.png");

    if (!pixmap.isNull()) {
        setPixmap(pixmap);
        setScale(0.8);
    } else {
        // اگه عکس پیدا نشد، یه تصویر ساده بساز
        QPixmap avatar(100, 100);
        avatar.fill(QColor(50, 50, 200));
        QPainter painter(&avatar);
        painter.setPen(Qt::white);
        painter.setFont(QFont("Vazirmatn", 12, QFont::Bold));
        painter.drawText(avatar.rect(), Qt::AlignCenter, "P");
        setPixmap(avatar);
        setScale(0.8);
    }
}

void player::writeToStream(QDataStream &out) const
{
    out << username << password << gold << Act << floor << maxHP << HP << mapID;
    out << potions << relics;
}

void player::readFromStream(QDataStream &in)
{
    in >> username >> password >> gold >> Act >> floor >> maxHP >> HP >> mapID;
    in >> potions >> relics;
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
        if (p.username == m_instance->oldUsername && p.password == m_instance->oldPassword   ||   p.username == m_instance->username && p.password == m_instance->password)
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

QVector<player> player::allPlayers()
{
    QVector<player> players(0);
    player p(nullptr);

    QFile file("players.bin");
    if (!file.open(QIODevice::ReadOnly))
        return players;
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_5);
    while(!in.atEnd()){
        p.readFromStream(in);
        players.push_back(p);
    }
    file.close();
    return players;
}

void player::ADD_BLOCK(int amount) {
    amount = buffManager.applyFrailToBlock(amount);
    block += amount;
    emit blockChanged(block);
}

void player::TAKE_DAMAGE(int damage) {
    damage = buffManager.applyVulnerableToDamage(damage);

    int remaining = damage - block;
    if (remaining > 0) {
        HP = qMax(0, HP - remaining);
        unblockedDamageTaken += remaining;
        block = 0;
    } else {
        block -= damage;
    }
    emit hpChanged(HP, maxHP);
    emit blockChanged(block);
}

void player::LOSE_HP(int amount) {
    HP = qMax(0, HP - amount);
    emit hpChanged(HP, maxHP);
}

void player::INCREASE_MAXHP(int amount) {
    maxHP += amount;
    HP += amount;
    emit hpChanged(HP, maxHP);
}

void player::SET_MAXHP(int newMax) {
    maxHP = newMax;
    HP = qMin(HP, maxHP);
    emit hpChanged(HP, maxHP);
}

void player::ADD_TO_HAND(Card* card){
    if(card && hand.size() < 10){
        hand.push_back(card);
        emit handUpdated();
    }
}

void player::REMOVE_FROM_HAND(Card* card){
    hand.removeAll(card);
    emit handUpdated();
}

void player::ADD_TO_DISCARDPILE(Card* card){
    if(card != NULL){
        discardPile.append(card);
    }
}

void player::ADD_TO_DRAWPILE(Card* card){
    if(card != NULL){
        drawPile.append(card);
    }
}

void player::ADD_TO_EXHAUSTPILE(Card* card ){
    if(card != NULL){
        exhaustPile.append(card);
    }
}

void player::SHUFFLE_DRAWPILE(){
    std::random_device rand;
    std::mt19937 g(rand());
    std::shuffle(drawPile.begin(), drawPile.end(), g);
}

void player::SHUFFLE_DISCARDPILE(){
    std::random_device rand;
    std::mt19937 g(rand());
    std::shuffle(discardPile.begin(), discardPile.end(), g);
}

void player::START_TURN()
{
    energy = 3;
    emit energyChanged(energy);

    buffManager.decreaseTurns();

    DRAW_CARD(5);
    if (!barricadeActive) {
        block = 0;
        emit blockChanged(block);
    }
}

void player::DRAW_CARD(int count){
    int draw = 0;
    while(draw < count){
        if(drawPile.isEmpty()){
            if(discardPile.isEmpty()){
                break;
            }
            drawPile = discardPile;
            discardPile.clear();
            SHUFFLE_DRAWPILE();
        }
        if(hand.size() >= 10){
            break;
        }
        Card* card = drawPile.takeLast();
        hand.append(card);
        draw++;
    }
    emit handUpdated();
}

void player::END_TURN(){
    energy = 0;
    emit energyChanged(energy);

    buffManager.applyMetallicizeAtEndOfTurn(block);

    QVector<Card*> retainCards;
    QVector<Card*> discardCards;
    QVector<Card*> exhaustCards;

    for(Card* card : hand){
        if(card->GETER_SETER_RETAIN()){
            retainCards.append(card);
        } else if(card->GETER_SETER_Ethereal()){
            exhaustCards.append(card);
        } else if(card->GETER_SETER_Exhaust()){
            exhaustCards.append(card);
        } else {
            discardCards.append(card);
        }
    }

    hand.clear();
    hand = retainCards;

    for(Card* card : discardCards){
        discardPile.append(card);
    }
    for(Card* card : exhaustCards){
        exhaustPile.append(card);
    }

    if(!barricadeActive){
        block = 0;
        emit blockChanged(block);
    }
    emit handUpdated();
}

void player::initializeDeck()
{
    // ===== پاک کردن کارت‌های قبلی =====
    qDeleteAll(drawPile);
    drawPile.clear();
    qDeleteAll(hand);
    hand.clear();
    qDeleteAll(discardPile);
    discardPile.clear();
    qDeleteAll(exhaustPile);
    exhaustPile.clear();

    // ===== لیست کارت‌ها =====
    QVector<Card*> allCards;

    // ===== اضافه کردن کارت‌ها =====
    allCards.append(new Strike());
    allCards.append(new TwinStrike());
    allCards.append(new BloodForBlood());
    allCards.append(new Hemokinesis());
    allCards.append(new Carnage());
    allCards.append(new Whirlwind());
    allCards.append(new Bludgeon());
    allCards.append(new Immolate());
    allCards.append(new Reaper());
    allCards.append(new Feed());

    // ===== رندوم کردن کارت‌ها =====
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allCards.begin(), allCards.end(), g);

    // ===== انتخاب ۵ کارت رندوم برای دست =====
    int cardCount = qMin(5, allCards.size());
    for (int i = 0; i < cardCount; ++i) {
        hand.append(allCards[i]);
    }

    // ===== بقیه کارت‌ها برن به drawPile =====
    for (int i = cardCount; i < allCards.size(); ++i) {
        drawPile.append(allCards[i]);
    }

    // ===== شافل کردن drawPile =====
    SHUFFLE_DRAWPILE();
}