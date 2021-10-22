#ifndef MYLIST_H
#define MYLIST_H

#include <QAbstractItemModel>
#include <QObject>

struct Car
{
    int speed;
    QString type;
    QString name;
    int power;
    int damage;
    QString status; //alive, dead, out

    Car()
    {
        speed = 0;
        type = "unknown type";
        name = "unknown object";
        power = 0;
        damage = 0;
        status = "alive";
    }

    Car (int speed, QString type, QString name, int power, int damage)
    {
        this->speed = speed;
        this->type = type;
        this->name = name;
        this->power = power;
        this->damage = damage;
        status = "alive";
    }
};

class MyList: public QAbstractListModel
{
    Q_OBJECT
public:
    MyList(QObject* parent = nullptr);
    enum contactRolse
    { // множество возможных значений поля
        NameRole = Qt::DisplayRole, // заголовок для элемента модели (для нас это имя)
        TypeRole = Qt::UserRole + 1,  // тип элемента
        SpeedRole = Qt::UserRole + 2,  // скорость
        PowerRole = Qt::UserRole + 3,  // кол-во орудий для противодействия
        DamageRole = Qt::UserRole + 4,  // ущерб
        StatusRole = Qt::UserRole + 5 //жизнь
    };
    QVariant data(const QModelIndex &index, int role) const; // функция доступа к данным
    int rowCount(const QModelIndex &parent) const; // количество элементов в модели
    void step();
public slots:
    void addCar(Car car); // добавить элемент
    void mysort (int role);
    void kill (const QString name);
    void focus (const QString name);
private:
    QList<Car> cars; // список элементов
    QHash<int, QByteArray> roles; // роли
};

#endif // MYLIST_H
