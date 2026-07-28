#ifndef CARDREMOVAL_H
#define CARDREMOVAL_H

#include <qgraphicsitem.h>


class CardRemoval : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit CardRemoval(QGraphicsItem *parent = nullptr);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void removalClicked();

};

#endif // CARDREMOVAL_H
