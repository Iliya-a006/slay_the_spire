#ifndef EVENTROOM_H
#define EVENTROOM_H

#include "room.h"

class EventRoom : public Room
{
public:
    explicit EventRoom(int index, QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // EVENTROOM_H
