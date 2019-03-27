#include "parallelsystem.h"

ParallelSystem::ParallelSystem(QString name) {
    this->name = name;
    this->itemsCount = 0;
}

void ParallelSystem::addItem(Item *item) {
    items.append(item);
    itemsCount++;
}

QString ParallelSystem::getName() const
{
    return name;
}

void ParallelSystem::setName(const QString &value) {
    name = value;
}

QList<double> ParallelSystem::getReliabilityByTime() const
{
    return reliabilityByTime;
}

void ParallelSystem::setReliabilityByTime(const QList<double> &value)
{
    reliabilityByTime = value;
}

int ParallelSystem::getItemsCount() const
{
    return itemsCount;
}

void ParallelSystem::setItemsCount(int value)
{
    itemsCount = value;
}
