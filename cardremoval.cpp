#include "cardremoval.h"

CardRemoval::CardRemoval(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/icons/images/card_removal_service"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void CardRemoval::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit removalClicked();
}
