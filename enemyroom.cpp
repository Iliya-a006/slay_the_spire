#include "enemyroom.h"

EnemyRoom::EnemyRoom(QGraphicsItem *parent) : Room(parent){

    setPixmap(QPixmap(":/icons/images/MonsterMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void EnemyRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}
