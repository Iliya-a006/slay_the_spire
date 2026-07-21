#ifndef MAP1_H
#define MAP1_H

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

    static Map1* instance();
    static void saveMap();
    static int selectedIndex;

private:
    Ui::Map1 *ui;
    friend class MainWindow;

    static Map1* m_instance;
    QGraphicsScene* m_scene;
    QGraphicsView* m_view;

    QVector<QVector<Room*>> floors;
    QVector<QVector<int>> floorsCode;
    QVector<int> route;
    QVector<Room*> accessibleRooms;
    void mapCoder();
    void loadMap();
    void printMap();
    void roadCreator();
    int roomHeigth(int floor);
    int roomWidth(int type);
    Room* roomCreator(int roomType, int roomIndex);


public slots:
    void onRoomExited(bool result);


};

#endif // MAP1_H
