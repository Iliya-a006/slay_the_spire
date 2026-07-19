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
    void setName(QString n){username = n;}
    QString getPassword(){return password;}
    void setPassword(QString p){password = p;}
    QString getOldName(){return oldUsername;}
    void setOldName(QString n){oldUsername = n;}
    QString getOldPassword(){return oldPassword;}
    void setOldPassword(QString p){oldPassword = p;}
    int getMapID(){return mapID;}
    void setMapID(int id){mapID = id;}


    static player* instance();
    static QVector<player> allPlayers();

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
