#ifndef VENDOR_H
#define VENDOR_H

#include <qgraphicsitem.h>


class Vendor : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Vendor(QGraphicsItem *parent = nullptr);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void VendorClicked();

};

#endif // VENDOR_H
