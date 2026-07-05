#ifndef CAMPSCENE_H
#define CAMPSCENE_H

#include <QWidget>

namespace Ui {
class CampScene;
}

class CampScene : public QWidget
{
    Q_OBJECT

public:
    explicit CampScene(QWidget *parent = nullptr);
    ~CampScene();

private:
    Ui::CampScene *ui;
};

#endif // CAMPSCENE_H
