#include "roomscene.h"
#include "map1.h"

RoomScene::RoomScene(QWidget *parent)
    : QWidget(parent)
{
    connect(this, &RoomScene::roomExited, Map1::instance(), &Map1::onRoomExited);
}

RoomScene::~RoomScene()
{

}
