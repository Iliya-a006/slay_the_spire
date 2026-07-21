#ifndef GOLDENSHRINEEVENT_H
#define GOLDENSHRINEEVENT_H

#include "event.h"

class GoldenShrineEvent : public Event
{
    Q_OBJECT
public:
    explicit GoldenShrineEvent(QWidget *parent = nullptr);
};

#endif // GOLDENSHRINEEVENT_H
