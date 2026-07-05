#include "shoproom.h"
#include "mainwindow.h"
#include "Page.h"

ShopRoom::ShopRoom(QGraphicsItem *parent) : Room(parent){

    setPixmap(QPixmap(":/icons/images/ShopMapIcon.png"));

    setAcceptedMouseButtons(Qt::LeftButton);
}

void ShopRoom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    MainWindow::changeStack((int)Page::Shop);
}
