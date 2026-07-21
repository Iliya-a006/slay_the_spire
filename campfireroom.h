#ifndef CAMPFIREROOM_H
#define CAMPFIREROOM_H

#include "room.h"

class CampfireRoom : public Room
{
public:
    explicit CampfireRoom(int index, QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CAMPFIREROOM_H
