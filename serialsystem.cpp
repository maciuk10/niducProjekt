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

double SerialSystem::getReliability() {
    return reliability;
}

void SerialSystem::setReliability() {
    double product = 1;
    QList<ParallelSystem*> systemItems = this->getItems();
    foreach(ParallelSystem* systemItem, systemItems){
        product = product*(systemItem->getReliability());
    }
    this->reliability = product;
}

void SerialSystem::setReliability(int year){
    QList<ParallelSystem*> parallels = this->getItems();
    foreach(ParallelSystem* parallel, parallels){
        QList<Item*> items = parallel->getItems();
        foreach(Item *item, items){
            item->setAvailability(year);
        }
        parallel->setReliability();
    }
    this->setReliability();
}

double SerialSystem::getMaxElementReliability() {
    QList <ParallelSystem*> systems = this->getItems();
    double maxReli = 0;
    foreach(ParallelSystem* system, systems){
        if(maxReli < system->getReliability()){
            maxReli = system->getReliability();
        }
    }
    if((int)maxReli == 1){
        maxReli = -1.0;
    }
    return maxReli;
}

double SerialSystem::getMinElementReliability() {
    QList <ParallelSystem*> systems = this->getItems();
    double minReli = 1.0;
    foreach(ParallelSystem* system, systems){
        if(minReli > system->getReliability()){
            minReli = system->getReliability();
        }
    }
    if((int)minReli == 1){
        minReli = -1.0;
    }
    return minReli;
}

double SerialSystem::getDowntime() {
    return (1.0 - getReliability()) * 8760.0;
}

double SerialSystem::getUptime() {
    return 8760.00000 - ((1.00000 - getReliability()) * 8760.00000);
}


int SerialSystem::getYearOfWork() const
{
    return yearOfWork;
}

void SerialSystem::setYearOfWork(int value) {
    yearOfWork = value;
}

SerialSystem::SerialSystem(QString name) {
    this->name = name;
    this->itemsCount = 0;
    this->yearOfWork = 0;
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
