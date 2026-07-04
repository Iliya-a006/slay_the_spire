#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>



class StatusBar : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBar(QWidget *parent = nullptr);
    ~StatusBar();
    static StatusBar* m_instance;
    static StatusBar* instance();

    void status(QString text, int mSeconds);

signals:
    void statusSignal(QString text, int mSeconds);

};

#endif // STATUSBAR_H
