#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QWidget>
#include <qscrollarea.h>


class leaderBoard : public QWidget
{
    Q_OBJECT

public:
    explicit leaderBoard(QWidget *parent = nullptr);
    ~leaderBoard();

private:
    QWidget* createRow(const QString &text1, const QString &text2, const QString &text3, const QString &text4);
    QScrollArea* createScrollableList(const QVector<std::array<QString,4>> &myItems);

};

#endif // LEADERBOARD_H
