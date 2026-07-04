#ifndef ENEMYROOM_H
#define ENEMYROOM_H

#include "room.h"

class EnemyRoom : public Room
{
public:
    explicit EnemyRoom(QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // ENEMYROOM_H
