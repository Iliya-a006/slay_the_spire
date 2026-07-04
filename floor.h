#ifndef FLOOR_H
#define FLOOR_H

#include "room.h"

class Floor
{
public:
    Floor();
    QVector<Room*> rooms;
};

#endif // FLOOR_H
