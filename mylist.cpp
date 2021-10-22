#include "mylist.h"

MyList::MyList(QObject* parent)
    :QAbstractListModel(parent)
{
    roles[NameRole] = "name";
    roles[TypeRole] = "type";
    roles[SpeedRole] = "speed";
    roles[PowerRole] = "power";
    roles[DamageRole] = "damage";
    roles[StatusRole] = "status";
}

QVariant MyList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() < 0 || index.row() > cars.count())
        return QVariant();
    const Car &ct = cars[index.row()];
    switch (role)
    {
        case Qt::DisplayRole:
            return ct.name;
            break;
        case Qt::UserRole + 1:
            return ct.type;
            break;
        case Qt::UserRole + 2:
            return ct.speed;
            break;
        case Qt::UserRole + 3:
            return ct.power;
            break;
        case Qt::UserRole + 4:
            return ct.damage;
            break;
        case Qt::UserRole + 5:
            return ct.status;
            break;
        default:
            return QVariant();
            break;
    }
}

void MyList::addCar(Car car)
{
    cars << car;
}

void MyList::mysort(int role)
{
    switch (role)
    {
        case Qt::DisplayRole:
            qSort(cars.begin(), cars.end(), [](const Car &a, const Car &b)
                                            {
                                                return a.name < b.name;
                                            });
        break;
        case Qt::UserRole + 1:
            qSort(cars.begin(), cars.end(), [](const Car &a, const Car &b)
                                            {
                                                return a.type < b.type;
                                            });
        break;
        case Qt::UserRole + 2:
            qSort(cars.begin(), cars.end(), [](const Car &a, const Car &b)
                                            {
                                                return a.speed < b.speed;
                                            });
        break;
        case Qt::UserRole + 3:
            qSort(cars.begin(), cars.end(), [](const Car &a, const Car &b)
                                            {
                                                return a.power < b.power;
                                            });
        break;
        case Qt::UserRole + 4:
            qSort(cars.begin(), cars.end(), [](const Car &a, const Car &b)
                                            {
                                                return a.damage < b.damage;
                                            });
        break;
        case Qt::UserRole + 5:
            qSort(cars.begin(), cars.end(), [](const Car &a, const Car &b)
                                            {
                                                return a.status < b.status;
                                            });
        break;
        default:
            break;
    }
}

void MyList::kill(const QString name)
{
    for (auto i = cars.begin(); i != cars.end(); i++)
    {
        if (i->name == name)
            i->status = "dead";
    }
}

void MyList::focus(const QString name)
{
    for (auto i = cars.begin(); i != cars.end(); i++)
    {
        if (i->name == name)
            i->status = "focus";
    }
}

int MyList::rowCount(const QModelIndex &parent) const
{
    return cars.size();
}

void MyList::step()
{
    for (auto i = cars.begin(); i != cars.end(); i++)
    {
        if (i->status != "focus" && i->status != "dead")
            i->speed--;
        if (i->speed < 0)
            i->status = "out";
    }
}
