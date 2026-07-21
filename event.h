#ifndef EVENT_H
#define EVENT_H

#include <qwidget.h>


struct EventOption {
    QString buttonText;
    std::function<void()> action;
};

class Event : public QWidget
{
    Q_OBJECT
public:
    explicit Event(QWidget *parent = nullptr);

    QVector<EventOption> eventOptions;
    void addOption(const EventOption &option);


protected:
    QString name;
    QString description;
    QString picture;


};

#endif // EVENT_H
