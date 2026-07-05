#include "room.h"
#include <qgraphicsscene.h>
#include <QVector>

Room::Room(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    //setPixmap(QPixmap(""));

}

void Room::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}


