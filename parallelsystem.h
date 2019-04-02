#ifndef PARALLELSYSTEM_H
#define PARALLELSYSTEM_H

#include <QString>
#include <QList>
#include <QMap>
#include <iostream>
#include "item.h"

class ParallelSystem {
private:
    QString name;
    QList<Item *> items;
    int itemsCount;
    double reliability;
public:
    ParallelSystem(QString name);
    void addItem(Item* item);
    void removeItem(Item* item);
    double countReliability();
    double countDownTime(int hours);
    QString getName() const;
    void setName(const QString &value);
    int getItemsCount() const;
    void setItemsCount(int value);
    double getReliability() const;
    void setReliability();
    QList<Item *> getItems() const;
    Item *getItem(int index);
};

#endif // PARALLELSYSTEM_H
