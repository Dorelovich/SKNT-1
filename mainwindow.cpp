#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _model = new MyList(this);
    _model->addCar(Car(5,"Земля","obj1",1,150));
    _model->addCar(Car(10,"Воздух","obj2",2,100));
    //_model->addCar(Car(3,"Вода","obj3",2,100));
    //_model->addCar(Car(6,"Вода","obj4",1,100));
    _model->mysort(258);

    proxyModel1 = new QSortFilterProxyModel(this);
    proxyModel1->setSourceModel(_model);
    proxyModel1->setFilterRole(261);
    proxyModel1->setFilterFixedString("alive");
    ui->listView->setModel(proxyModel1);

    proxyModel2 = new QSortFilterProxyModel(this);
    proxyModel2->setSourceModel(_model);
    proxyModel2->setFilterRole(261);
    proxyModel2->setFilterFixedString("dead");
    ui->listView_2->setModel(proxyModel2);

    proxyModel3 = new QSortFilterProxyModel(this);
    proxyModel3->setSourceModel(_model);
    proxyModel3->setFilterRole(261);
    proxyModel3->setFilterFixedString("out");
    ui->listView_3->setModel(proxyModel3);

    number_weapons = 0;
    timer = new QTimer();
    time = new QTime(0,0,0);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
}

MainWindow::~MainWindow()
{
    delete ui;
    if (timer) delete timer;
    if (time) delete time;
    if (proxyModel1) delete proxyModel1;
    if (proxyModel2) delete proxyModel2;
    if (proxyModel3) delete proxyModel3;
    if (_model) delete _model;
}

QVariant MainWindow::count_damage()
{
    int result = 0;
    for (int i = 0; i < ui->listView_3->batchSize(); i++)
    {
        result += ui->listView_3->model()->index(i,0).data(260).toInt();
    }
    return result;
}

QVariant MainWindow::count_peace()
{
    int result = 0;
    for (int i = 0; i < ui->listView_2->batchSize(); i++)
    {
        result += ui->listView_2->model()->index(i,0).data(260).toInt();
    }
    return result;
}

void MainWindow::slotTimerAlarm()
{
    ui->label_8->setText(time->toString("hh:mm:ss"));
    *time = time->addSecs(1);

    if (ui->listView->model()->index(0,0).data(257).toString() == "Земля") //если объект типа земля
    {
        if (number_weapons >= ui->listView->model()->index(0,0).data(259).toInt()) //и если мы можем его взять на мушку
        {
            tg_list.push_back(target(ui->listView->model()->index(0,0).data(0).toString(), //берём на мушку
                                     ui->spinBox->value(),ui->listView->model()->index(0,0).data(259).toInt()));
            number_weapons -= ui->listView->model()->index(0,0).data(259).toInt(); //уменьшаем количество орудий
            _model->focus(ui->listView->model()->index(0,0).data(0).toString()); //убрали модель из списка
        }
    }

    if (ui->listView->model()->index(0,0).data(257).toString() == "Вода") //если объект типа вода
    {
        if (number_weapons >= ui->listView->model()->index(0,0).data(259).toInt()) //и если мы можем его взять на мушку
        {
            tg_list.push_back(target(ui->listView->model()->index(0,0).data(0).toString(), //берём на мушку
                                     ui->spinBox_5->value(),ui->listView->model()->index(0,0).data(259).toInt()));
            number_weapons -= ui->listView->model()->index(0,0).data(259).toInt(); //уменьшаем количество орудий
            _model->focus(ui->listView->model()->index(0,0).data(0).toString()); //убрали модель из списка
        }
    }

    if (ui->listView->model()->index(0,0).data(257).toString() == "Воздух") //если объект типа воздух
    {
        if (number_weapons >= ui->listView->model()->index(0,0).data(259).toInt()) //и если мы можем его взять на мушку
        {
            tg_list.push_back(target(ui->listView->model()->index(0,0).data(0).toString(), //берём на мушку
                                     ui->spinBox_7->value(),ui->listView->model()->index(0,0).data(259).toInt()));
            number_weapons -= ui->listView->model()->index(0,0).data(259).toInt(); //уменьшаем количество орудий
            _model->focus(ui->listView->model()->index(0,0).data(0).toString()); //убрали модель из списка
        }
    }

    _model->step(); //делаю шаг
    for (auto i = tg_list.begin(); i != tg_list.end(); i++) //провожу уничтожение целей
    {
        i->time--;
        if (i->time < 0)
        {
            number_weapons += i->weapons;
            _model->kill(i->name);
            tg_list.pop_front();
        }
    }

    proxyModel1->setFilterFixedString("alive");
    ui->listView->setModel(proxyModel1);

    proxyModel2->setFilterFixedString("dead");
    ui->listView_2->setModel(proxyModel2);

    proxyModel3->setFilterFixedString("out");
    ui->listView_3->setModel(proxyModel3);

    ui->label_15->setText(count_damage().toString());
    ui->label_14->setText(count_peace().toString());
}

void MainWindow::on_action_triggered()
{
    timer->start(1000);
    number_weapons = ui->spinBox_4->value();
    ui->spinBox->setDisabled(true);
    ui->spinBox_4->setDisabled(true);
    ui->spinBox_5->setDisabled(true);
    ui->spinBox_7->setDisabled(true);
}


void MainWindow::on_action_2_triggered()
{
    timer->stop();
}

