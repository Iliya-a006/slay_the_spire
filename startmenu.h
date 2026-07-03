#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include <qpushbutton.h>


class startMenu : public QWidget
{
    Q_OBJECT

public:
    explicit startMenu(QWidget *parent = nullptr);
    ~startMenu();

private:
    QPushButton* singleButton;
    QPushButton* multiButton;
    QPushButton* backButton;
};

#endif // STARTMENU_H
