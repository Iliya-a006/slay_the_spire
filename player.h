#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QVector>
#include <QDataStream>


class player
{
public:
    explicit player();
    QString getName(){return username;}
    int getMapID(){return mapID;}
    void setMapID(int id){mapID = id;}
    int getAct(){return Act;}
    void setAct(int a){Act = a;}
    int getFloor(){return floor;}
    void setFloor(int f){floor = f;}

    static player* instance();
    static QVector<player> allPlayers();

private:
    static player* m_instance;

    QString username;
    QString password;
    int gold;
    int Act;
    int floor;
    int maxHP;
    int HP;
    int mapID = -1;
    QVector<int> cards/*(20)*/;
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
