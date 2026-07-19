#ifndef REDX_H
#define REDX_H

#include <qgraphicsitem.h>

class RedX: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit RedX(QGraphicsItem *parent = nullptr);
};

#endif // REDX_H
