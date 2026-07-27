#ifndef CHEST_H
#define CHEST_H

#include <qgraphicsitem.h>


class Chest : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Chest(QGraphicsItem *parent = nullptr);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void ChestClicked();

};

#endif // CHEST_H
