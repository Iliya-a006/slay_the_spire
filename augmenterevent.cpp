#include "augmenterevent.h"
#include "player.h"

AugmenterEvent::AugmenterEvent()
{
    this->name = "Augmenter";
    this->description = "A man with an eyepatch and a devilish grin strides up to you.\n\nShady Man: 'Hey there, stranger. Interested in advancing science? I can make you stronger than any training or blessing. You're gonna need it if you're one of those heroes with a death wish.'\n\nShady Man: 'What'ya say?'";
    this->picture = ":/prefix1/eventPictures/augmenter.png";

    EventOption testJAX = {"Test J.A.X",
                           "Shady Man: 'Excellent.' The man hands over a dangerous looking syringe filled with a glowing liquid before skulking off into a shadowy alleyway.",
                           [](){
                               //player::instance()->ADD_TO_DRAWPILE( JAX );
                           }};
    this->addOption(testJAX);

    EventOption becomeTestSubject = {"Become Test Subject",
                                     "Shady Man: 'Superb.' The man injects you with three unknown substances and pulls out a notepad. As you begin to feel light-headed, he starts to frantically write down notes. Losing track of time completely, by the time you regain your senses, the shady character has disappeared.",
                                     [](){
                                         // choose two cards and transform them
                                     }};
    this->addOption(becomeTestSubject);

    EventOption ingestMutagens = {"Ingest Mutagens",
                                  "Shady Man: 'Marvelous.' You quaff the mysterious substance. Immediately, you are invigorated and feel your muscle fibers twitch.",
                                  [](){
                                      // recieve relic Mutagenic Strength
                                  }};
    this->addOption(ingestMutagens);
}





