#ifndef SHOPROOM_H
#define SHOPROOM_H

#include "room.h"

class ShopRoom : public Room
{
public:
    explicit ShopRoom(QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // SHOPROOM_H
