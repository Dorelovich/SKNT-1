#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mylist.h"
#include <QTimer>
#include <QTime>
#include <QSortFilterProxyModel>

struct target
{
    QString name;
    int time;
    int weapons;

    target()
    {
        name = "unknown object";
        time = 0;
    }
    target (QString name, int time, int weapons)
    {
        this->name = name;
        this->time = time;
        this->weapons = weapons;
    }
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MyList *_model;
    QList<target> tg_list;
    int number_weapons;
    QTimer *timer;
    QTime *time;
    QSortFilterProxyModel *proxyModel1, *proxyModel2, *proxyModel3;

    QVariant count_damage();
    QVariant count_peace();

private slots:
    void slotTimerAlarm();
    void on_action_triggered();
    void on_action_2_triggered();
};
#endif // MAINWINDOW_H
