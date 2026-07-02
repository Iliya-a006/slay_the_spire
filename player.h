#ifndef PLAYER_H
#define PLAYER_H

// #include "buff_debuff.h"
// #include "card.h"
// #include "potion.h"
// #include "relic.h"
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QDataStream>


class player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit player(QGraphicsItem *parent = nullptr);
    //friend class login;

    static player* instance();

private:
    static player* m_instance;

    QString username;
    QString password;
    int gold;
    int Act;
    int floor;
    int maxHP;
    int HP;
    QVector<int> cards/*(20)*/;
    QVector<int> buff_debuffs;
    QVector<int> potions;
    QVector<int> relics;

public:
    void writeToStream(QDataStream &out) const;
    void readFromStream(QDataStream& in);
    static bool appendPlayer(QString name, QString pass);
    static bool findPlayer(QString name, QString pass);
};

#endif // PLAYER_H
