#include "chest.h"

Chest::Chest(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/icons/images/LargeChest.png"));

    setAcceptedMouseButtons(Qt::LeftButton);

}

void Chest::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit ChestClicked();
}
