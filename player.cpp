#include "player.h"
#include <QFile>
#include <QDataStream>

player::player()
{
    gold = 0;
    Act = 1;
    floor = 0;
    maxHP = 80;
    HP = maxHP;
    mapID = -1;
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
    out << cards << /*buff_debuffs << */potions << relics;
}

void player::readFromStream(QDataStream &in)
{
    in >> username >> password >> gold >> Act >> floor >> maxHP >> HP >> mapID;
    in >> cards >> /*buff_debuffs >> */potions >> relics;
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





