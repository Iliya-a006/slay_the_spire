#ifndef EVENTSCENE_H
#define EVENTSCENE_H

#include <QWidget>

namespace Ui {
class EventScene;
}

class EventScene : public QWidget
{
    Q_OBJECT

public:
    explicit EventScene(QWidget *parent = nullptr);
    ~EventScene();

private:
    Ui::EventScene *ui;
};

#endif // EVENTSCENE_H
