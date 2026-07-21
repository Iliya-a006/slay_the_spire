#include "goldenshrineevent.h"
#include "player.h"

GoldenShrineEvent::GoldenShrineEvent(QWidget *parent)
{
    this->name = "Golden Shrine";
    this->description = "";
    this->picture = "";

    EventOption pray = {"Pray", [](){
                             player::instance()->changeGold(100);
                        }};
    this->addOption(pray);
    EventOption leave = {"Leave", [](){
                            // leave signal to map
                        }};
}
