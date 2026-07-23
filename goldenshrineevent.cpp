#include "goldenshrineevent.h"
#include "player.h"

GoldenShrineEvent::GoldenShrineEvent()
{
    this->name = "Golden Shrine";
    this->description = "Before you lies an elaborate shrine to an ancient spirit.";
    this->picture = ":/prefix1/eventPictures/goldenIdol.png";

    EventOption pray = {"Pray",
                        "As your hand touches the shrine, gold rains from the ceiling showering you in riches."
                        , [](){
                             player::instance()->changeGold(100);
                        }};
    this->addOption(pray);

    EventOption leave = {"Leave",
                         "You ignore the shrine."
                         , [](){}};
    this->addOption(leave);
}
