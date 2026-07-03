#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    static QStackedWidget* m_stack;

private:
    Ui::MainWindow *ui;

protected:
    void paintEvent(QPaintEvent *event) override;
    QVector<QString> backgrounds;

};
#endif // MAINWINDOW_H
