#include "facetraderevent.h"
#include <QRandomGenerator>
#include "player.h"

FaceTraderEvent::FaceTraderEvent()
{
    this->name = "Face Trader";
    this->picture = ":/prefix1/eventPictures/faceTrader.png";
    this->description = "You walk by an eerie statue holding several masks... Something behind you softly whispers, 'Stop.' You swerve around to face the statue which is now facing you! On closer inspection, it's not a statue but a statuesque, gaunt man. Is he even breathing?\n\nEerie Man: Face. Let me touch? Maybe trade?";

    EventOption touch = {"Touch",
                         "Eerie Man: Compensation. Compensation. Mechanically, he cranes out a neat stack of gold and places it into your pouch.\n\nEerie Man: What a nice face. Nice face. While he touches your face, you begin to feel your life drain out of it! During this, his mask falls off and shatters. Screaming, he quickly covers his face with all six arms dropping even more masks! Amidst all the screaming and shattering, you escape. His face was completely blank."
                         , [](){
                             int percent = QRandomGenerator::global()->bounded(6) + 5;
                             player::instance()->SET_MAXHP(player::instance()->GETER_MAXHP() * (100 - percent) / 100);
                             player::instance()->changeGold(75);
                         }
    };
    this->addOption(touch);

    EventOption  trade = {"Trade",
                            "Eerie Man: 'For me? FOR ME? Oh yes.. Yes. Yes.. mmm...' You see one of his arms flicker, and your face is in its hand! Your face has been swapped.\n\nEerie Man: 'Nice face. Nice face.'",
                         [](){
                             // recieve a random relic of: Face of Cleric / Gremlin Visage / Cultist Headpiece
                         }
    };
    this->addOption(trade);

    EventOption leave = {"Leave",
                         "'Stop. Stop. Stop. Stop. Stop.' This was probably the right call."
                         , [](){}};
    this->addOption(leave);
}






