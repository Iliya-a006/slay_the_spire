#ifndef BOSSROOM_H
#define BOSSROOM_H

#include "room.h"

class BossRoom : public Room
{
public:
    explicit BossRoom(QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // BOSSROOM_H
