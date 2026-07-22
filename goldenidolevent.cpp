#include "goldenidolevent.h"
#include "player.h"

GoldenIdolEvent::GoldenIdolEvent()
{
    this->name = "Golden Idol";
    this->description = "You come across an inconspicuous pedestal with a shining gold idol sitting peacefully atop. It looks incredibly valuable. You sure don't see any traps nearby.";
    this->picture = ":/prefix1/eventPictures/glodenShrine.png";

    EventOption steal = {"Steal",
                         "",
                         [](){
                             // recieve relic Golden Idol
                             player::instance()->SET_MAXHP(player::instance()->GETER_MAXHP() - 5);
                         }};
    this->addOption(steal);

    EventOption leave = {"Leave",
                         "If there was ever an obvious trap, this would be it. You decide not to interfere with objects placed upon pedestals."
                         , [](){}};
    this->addOption(leave);
}
