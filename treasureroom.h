#ifndef TREASUREROOM_H
#define TREASUREROOM_H

#include "room.h"

class TreasureRoom : public Room
{
public:
    explicit TreasureRoom(QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // TREASUREROOM_H
