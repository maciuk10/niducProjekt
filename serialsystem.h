#ifndef SERIALSYSTEM_H
#define SERIALSYSTEM_H

#include <QString>
#include <QList>
#include <QDebug>
#include "item.h"
#include "parallelsystem.h"

class SerialSystem
{
private:
    QString name;
    QList<ParallelSystem *> items;
    int itemsCount;
    double reliability;
    int yearOfWork;
public:
    SerialSystem(QString name);
    QString getName() const;
    void setName(const QString &value);
    void addItems(ParallelSystem *parallelSystem);
    int getItemsCount() const;
    void setItemsCount(int value);
    double calculateReliability() const;
    QList<ParallelSystem *> getItems() const;
    void setItems(const QList<ParallelSystem *> &value);
    ParallelSystem *getParallelSystemByName(QString name);
    double getReliability();
    void setReliability();
    void setReliability(int year);
    double getMaxElementReliability();
    double getMinElementReliability();
    double getDowntime();
    double getUptime();
    int getYearOfWork() const;
    void setYearOfWork(int value);
};

#endif // SERIALSYSTEM_H
