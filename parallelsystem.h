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
    QList<Item*> items;
    QList<double> reliabilityByTime;
    int itemsCount;
public:
    ParallelSystem(QString name);
    void addItem(Item* item);
    void removeItem(Item* item);
    double countReliability();
    double countDownTime(int hours);
    QString getName() const;
    void setName(const QString &value);
    QList<double> getReliabilityByTime() const;
    void setReliabilityByTime(const QList<double> &value);
    int getItemsCount() const;
    void setItemsCount(int value);
};

#endif // PARALLELSYSTEM_H
