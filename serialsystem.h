#ifndef SERIALSYSTEM_H
#define SERIALSYSTEM_H

#include <QString>
#include <QList>
#include "item.h"
#include "parallelsystem.h"

class SerialSystem
{
private:
    QString name;
    QList<ParallelSystem *> items;
    int itemsCount;
    QList<double> reliabilityByTime;
public:
    SerialSystem(QString name);
    QString getName() const;
    void setName(const QString &value);
    void addItems(ParallelSystem *parallelSystem);
    int getItemsCount() const;
    void setItemsCount(int value);
    QList<double> getReliabilityByTime() const;
    void setReliabilityByTime(const QList<double> &value);
    double calculateReliability() const;
    QList<ParallelSystem *> getItems() const;
    void setItems(const QList<ParallelSystem *> &value);
    ParallelSystem *getParallelSystemByName(QString name);
};

#endif // SERIALSYSTEM_H
