#include "ominousforgeevent.h"

OminousForgeEvent::OminousForgeEvent()
{
    this->name = "Ominuous Forge";
    this->description = "You duck into a small hut. Inside, you find what appears to be a forge. The smithing tools are covered with dust, yet a fire roars inside the furnace. You feel on edge...";
    this->picture = ":/prefix1/eventPictures/ominousForge.png";

    EventOption forge = {"Forge",
                         "You decide to put the forge to use and...\nCLANG CLAAANG CLANG!\n...improve your arsenal!",
                         [](){
                             // upgrade a card
                         }};
    this->addOption(forge);

    EventOption rummage = {"Rummage",
                           "You decide to see if you can find anything of use. After uncovering tarps, looking through boxes, and checking nooks and crannies, you find a dust covered relic!.\nTaking the relic, you can't shake a sudden feeling of sharp pain as you exit the hut. Maybe you disturbed some sort of spirit?",
                           [](){
                                // recieve relic warped tongs
                               //recieve a curse card
                           }};
    this->addOption(rummage);

    EventOption leave = {"Leave",
                         "There doesn't seem to be anything of use. You exit the way you came, the flames of the furnace casting eerie shadows on the walls inside the hut..",
                         [](){}};
    this->addOption(leave);
}







