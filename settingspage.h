#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>
#include <qlabel.h>
#include <qpushbutton.h>


class SettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);
    ~SettingsPage();

private:
    QString buttonStyle;
    QLabel* settingsLabel;
    QPushButton* nameButton;
    QPushButton* passwordButton;
    QLabel* soundLabel;
    QPushButton *soundButton;
    QPushButton* backButton;

};

#endif // SETTINGSPAGE_H
