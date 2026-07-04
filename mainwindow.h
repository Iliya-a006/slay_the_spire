#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QGraphicsView>
#include <qstatusbar.h>

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
    static void changeStack(int page);
    QStatusBar* m_statusBar;

private:
    Ui::MainWindow *ui;


protected:
    void paintEvent(QPaintEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    QVector<QString> backgrounds;

private slots:
    void onLoginSuccess();
    void statusRecieve(QString text, int mSeconds);

};
#endif // MAINWINDOW_H
