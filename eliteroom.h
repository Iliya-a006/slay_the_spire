#ifndef ELITEROOM_H
#define ELITEROOM_H

#include "room.h"

class EliteRoom : public Room
{
public:
    explicit EliteRoom(int index, QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // ELITEROOM_H
