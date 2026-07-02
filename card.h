#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QGraphicsPixmapItem>

class Card : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Card(QGraphicsItem *parent = nullptr);

    int ID;

private:

};

#endif // CARD_H
