#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QWidget>
#include <qboxlayout.h>
#include <qscrollarea.h>


class leaderBoard : public QWidget
{
    Q_OBJECT
public:
    static leaderBoard* instance(QWidget *parent = nullptr);
    static void refreshBoard();
    ~leaderBoard();

private:
    explicit leaderBoard(QWidget *parent = nullptr);

    QWidget* createRow(const QString &text1, const QString &text2,
                       const QString &text3, const QString &text4);
    QScrollArea* createScrollableList(const QVector<std::array<QString,4>> &myItems);
    void refresh();

    static leaderBoard *m_instance;

    QVBoxLayout *m_outerLayout = nullptr;
    QScrollArea *m_list = nullptr;
};

#endif // LEADERBOARD_H
