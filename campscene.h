#ifndef CAMPSCENE_H
#define CAMPSCENE_H

#include "roomscene.h"
#include <QWidget>
#include <qlabel.h>
#include <qpushbutton.h>

class CampScene : public RoomScene
{
    Q_OBJECT

public:
    explicit CampScene(QWidget *parent = nullptr);
    ~CampScene();

    void resetRoom() override;

private:
    QPushButton* restButton;
    QPushButton* smithButton;
    QPushButton* recallButton;
    QLabel* titleLabel;
    QLabel* restLabel;
    QLabel* smithLabel;
    QLabel* recallLabel;
};

#endif // CAMPSCENE_H
