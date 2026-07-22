#include "joustevent.h"
#include <QRandomGenerator>
#include "player.h"

JoustEvent::JoustEvent()
{
    this->name = "The Joust";
    this->description = "As you make your way through the large buildings you come across a long narrow bridge and spot knights on either side, facing one another. You approach...\n\nKnight: 'HALT!' A knight forcefully gestures you to stop with its giant lance.\n\nKnight: 'Today is the day I must settle the score with the murderer of my beloved pet, Noodles. Until then, you may not pass.'\n\nKnight: 'Fellow witness, why don't you bet on who you think will emerge victorious?'";
    this->picture = ":/prefix1/eventPictures/joust.png";

    EventOption murderer = {"Murderer",
                             "Knight: 'I can't believe you're betting against Noodles!' Furious, he clamps down his helmet and rushes towards his nemesis.",
                             [](){
                                player::instance()->changeGold(-50);
                                int chance = QRandomGenerator::global()->bounded(10);
                                if (chance < 7)
                                    player::instance()->changeGold(100);
                            }};
    this->addOption(murderer);

    EventOption owner = {"Owner",
                         "Knight: Give me strength, Noodles! Clamping down his helmet, the knight charges forward.",
                         [](){
                             player::instance()->changeGold(-50);
                             int chance = QRandomGenerator::global()->bounded(10);
                             if (chance < 3)
                                 player::instance()->changeGold(250);
                         }};
    this->addOption(owner);
}
