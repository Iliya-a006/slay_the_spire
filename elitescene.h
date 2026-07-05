#ifndef ELITESCENE_H
#define ELITESCENE_H

#include <QWidget>

namespace Ui {
class EliteScene;
}

class EliteScene : public QWidget
{
    Q_OBJECT

public:
    explicit EliteScene(QWidget *parent = nullptr);
    ~EliteScene();

private:
    Ui::EliteScene *ui;
};

#endif // ELITESCENE_H
