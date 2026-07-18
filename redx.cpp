#include "redx.h"

RedX::RedX(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/icons/images/RedX_blood.png"));
}
