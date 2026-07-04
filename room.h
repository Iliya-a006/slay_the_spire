#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QGraphicsPixmapItem>
//#include <QGraphicsSceneMouseEvent>

class Room : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Room(QGraphicsItem *parent = nullptr);

    QVector<Room*> nextRooms;
    QVector<Room*> previouseRooms;

// protected:
//     void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // ROOM_H
