#ifndef ROOMSCENE_H
#define ROOMSCENE_H

#include <qgraphicsscene.h>
#include <qwidget.h>

class RoomScene : public QWidget
{
    Q_OBJECT

public:
    explicit RoomScene(QWidget *parent = nullptr);
    ~RoomScene();

    virtual void resetRoom() = 0;

protected:
    QGraphicsScene* m_scene;
    QGraphicsView* m_view;

signals:
    void roomExited(bool result);
};

#endif // ROOMSCENE_H
