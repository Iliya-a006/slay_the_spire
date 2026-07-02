#ifndef BUFF_DEBUFF_H
#define BUFF_DEBUFF_H

#include <QWidget>
#include <QGraphicsPixmapItem>

class buff_debuff : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit buff_debuff(QGraphicsItem *parent = nullptr);

    int ID;
private:

};

#endif // BUFF_DEBUFF_H
