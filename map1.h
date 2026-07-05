#ifndef MAP1_H
#define MAP1_H

#include "floor.h"
#include "room.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace Ui {
class Map1;
}

class Map1 : public QWidget
{
    Q_OBJECT

public:
    explicit Map1(QWidget *parent = nullptr);
    ~Map1();

private:
    Ui::Map1 *ui;

    QGraphicsScene* m_scene;
    QGraphicsView* m_view;

    //QVector<Floor*> floors;
    QVector<QVector<Room*>> floors;
    QVector<QVector<int>> floorsCode;
    void mapCoder();
    void loadMap();
    void printMap();
    void roadCreator();
    int roomHeigth(int floor);
    int roomWidth(int type);
    Room* roomCreator(int roomType);


};

#endif // MAP1_H
