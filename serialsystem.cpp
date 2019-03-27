#include "serialsystem.h"

QList<ParallelSystem *> SerialSystem::getItems() const
{
    return items;
}

void SerialSystem::setItems(const QList<ParallelSystem *> &value)
{
    items = value;
}

ParallelSystem *SerialSystem::getParallelSystemByName(QString name) {
    foreach(ParallelSystem* ps, items){
        if(ps->getName() == name){
            return ps;
        }
    }
    return nullptr;
}

SerialSystem::SerialSystem(QString name) {
    this->name = name;
    this->itemsCount = 0;
}

QString SerialSystem::getName() const {
    return name;
}

void SerialSystem::setName(const QString &value) {
    name = value;
}

void SerialSystem::addItems(ParallelSystem *parallelSystem) {
    items.append(parallelSystem);
}

int SerialSystem::getItemsCount() const {
    return itemsCount;
}

void SerialSystem::setItemsCount(int value) {
    itemsCount = value;
}

QList<double> SerialSystem::getReliabilityByTime() const {
    return reliabilityByTime;
}

void SerialSystem::setReliabilityByTime(const QList<double> &value) {
    reliabilityByTime = value;
}
