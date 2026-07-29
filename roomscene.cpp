#include "roomscene.h"
#include "map1.h"
#include "topbar.h"
#include "player.h"
#include "screensize.h"

RoomScene::RoomScene(QWidget *parent)
    : QWidget(parent)
{
    connect(this, &RoomScene::roomExited, Map1::instance(), &Map1::onRoomExited);
}

void RoomScene::updateBar()
{
    TopBar::instance(this)->setPlayerName(player::instance()->getName());
    TopBar::instance()->setGeometry(0, 0, ScreenSize::getWidth(), 40);
    TopBar::instance()->setHP(player::instance()->GETER_HP(), player::instance()->GETER_MAXHP());
    TopBar::instance()->setGold(player::instance()->GETER_GOLD());
    TopBar::instance()->setFloor(player::instance()->getFloor());
}

RoomScene::~RoomScene()
{

}
