#ifndef RELIC_H
#define RELIC_H

#include <QWidget>
#include <QGraphicsPixmapItem>

class Relic : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Relic(QGraphicsItem *parent = nullptr);

    int ID;

private:

};

#endif // RELIC_H
