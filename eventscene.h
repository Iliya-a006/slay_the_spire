#ifndef EVENTSCENE_H
#define EVENTSCENE_H

#include "roomscene.h"
#include <QWidget>
#include <qframe.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include "event.h"

class EventScene : public RoomScene
{
    Q_OBJECT

public:
    explicit EventScene(QWidget *parent = nullptr);
    ~EventScene();

    void resetRoom() override;

private:
    Event* event = nullptr;
    //QGraphicsPixmapItem *picture;
    QLabel* pictureLabel;
    void showEvent();
    void goToLeavePage(int i);

    QFrame* frame;
    QLabel* nameLabel;
    QLabel* describtionLabel;
    QVector<QPushButton*> buttons;
    QPushButton* leaveButton;
    QString labelStyle = "QLabel {"
                         "   color: white;"
                         "   font-size: 14px;"
                         "   font-family: 'Segoe Print';"
                         "}";
    QString buttonStyle = R"(
    QPushButton {
        background-color: #3a5a78;
        border: 2px solid #6b93b5;
        border-radius: 6px;
        color: #ffffff;
        font-size: 14px;
        font-weight: bold;
        font-style: italic;
        font-family: 'Segoe Print';
        padding: 8px 16px;
    }
    QPushButton:hover {
        background-color: #47698a;
        border: 2px solid #8ab0d4;
    }
    QPushButton:pressed {
        background-color: #2c4560;
    }
    )";
};

#endif // EVENTSCENE_H





