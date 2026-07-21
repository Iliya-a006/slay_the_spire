#include "room.h"
#include <qgraphicsscene.h>
#include <QVector>

Room::Room(int index, QGraphicsItem *parent)
    : index(index), QGraphicsPixmapItem(parent)
{

}

void Room::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}


