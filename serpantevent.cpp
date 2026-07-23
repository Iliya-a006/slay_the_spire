#include "serpantevent.h"
#include "player.h"

SerpantEvent::SerpantEvent()
{
    this->name = "The Ssssssserpent";
    this->description = "You walk into a room to find a large hole in the ground. As you approach the hole, an enormous serpent creature appears from within.\n\nSerpent: 'Ho hooo! Hello hello! what have we got here? Hello adventurer, I ask a simple question.'\n\nSerpent: 'The most fulfilling of lives is that in which you can buy anything!'\n\nSerpent: 'Do you agree?'";
    this->picture = ":/prefix1/eventPictures/serpant.png";

    EventOption agree = {"Agree",
                         "Serpent: 'Yeeeeeeeeesssssssssssssssssssssssssssssssssssssssssssss'\n\nSerpent: 'Thissss will all be worthhh it.'\n\nSerpent: '...ssSSSs..... ss... ssssss....!' The serpent rears its head and blasts a stream of gold upwards! It is amazing and terrifying simultaneously. You gather all the gold, thank the snake, and get going.",
                         [](){
                             player::instance()->changeGold(175);
                             // recieve curse doubt
                         }};
    this->addOption(agree);
}
