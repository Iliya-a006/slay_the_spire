#ifndef MAP1_H
#define MAP1_H

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
};

#endif // MAP1_H
