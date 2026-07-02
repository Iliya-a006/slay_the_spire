#ifndef POTION_H
#define POTION_H

#include <QWidget>
#include <QGraphicsPixmapItem>

class Potion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Potion(QGraphicsItem *parent = nullptr);

    int ID;

private:

};

#endif // POTION_H
