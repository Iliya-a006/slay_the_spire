#include "vendor.h"
#include <qgraphicsitem.h>

Vendor::Vendor(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/characters/images/vendor.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void Vendor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit VendorClicked();
}
