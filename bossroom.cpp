#include "bossroom.h"
#include "Page.h"
#include "mainwindow.h"

BossRoom::BossRoom(QGraphicsItem *parent) : Room(parent) {

    setPixmap(QPixmap(":/icons/images/BossMapIcon2.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void BossRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->accessible)
        return;
    Q_UNUSED(event);

    MainWindow::changeStack((int)Page::Boss);
}
