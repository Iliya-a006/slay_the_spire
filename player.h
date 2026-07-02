#ifndef PLAYER_H
#define PLAYER_H

#include "buff_debuff.h"
#include "card.h"
#include "potion.h"
#include "relic.h"
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QVector>


class player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit player(QGraphicsItem *parent = nullptr);

private:
    QString username;
    QString password;
    int gold;
    int Act;
    int floor;
    int HP;
    int maxHP;
    QVector<int> cards;
    QVector<int> buff_debuffs;
    QVector<int> potions;
    QVector<int> relics;
};

#endif // PLAYER_H
