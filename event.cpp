#include "event.h"

Event::Event(QWidget *parent)
{

}

void Event::addOption(const EventOption &option)
{
    eventOptions.push_back(option);
}
