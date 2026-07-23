#include "labevent.h"

LabEvent::LabEvent()
{
    this->name = "Lab";
    this->description = "You find yourself in a room filled with racks of test tubes, beakers, flasks, forceps, pinch clamps, stirring rods, tongs, goggles, funnels, pipets, cylinders, condensers, and even a rare spiral tube of glass. Why do you know the name of all these tools? It doesn't matter, you take a look around.";
    this->picture = ":/prefix1/eventPictures/lab.png";

    EventOption search = {"Search",
                          "",
                          [](){
                              // obtain three random potions
                          }};
    this->addOption(search);
}
