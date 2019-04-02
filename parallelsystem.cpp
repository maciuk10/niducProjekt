#include "parallelsystem.h"

double ParallelSystem::getReliability() const {
    return reliability;
}

QList<Item *> ParallelSystem::getItems() const {
    return items;
}

Item *ParallelSystem::getItem(int index) {
    if(index >= 0 && index < getItemsCount()){
        QList<Item*> items = getItems();
        for(int i = 0; i < getItemsCount(); i++){
            if(i == index){
                return items[i];
            }
        }
    }else {
        return nullptr;
    }
}

void ParallelSystem::setReliability() {
    QList<Item*> systemItems = this->getItems();
    double product = 1;
    foreach(Item* sysItem, systemItems){
        product = product * (1 - sysItem->getAvailability());
    }
    product = 1 - product;
    this->reliability = product;
}

ParallelSystem::ParallelSystem(QString name) {
    this->name = name;
    this->itemsCount = 0;
}

void ParallelSystem::addItem(Item *item) {
    items.append(item);
    itemsCount++;
}

void ParallelSystem::removeItem(Item *item) {
    items.removeOne(item);
    itemsCount--;
}

QString ParallelSystem::getName() const
{
    return name;
}

void ParallelSystem::setName(const QString &value) {
    name = value;
}

int ParallelSystem::getItemsCount() const
{
    return itemsCount;
}

void ParallelSystem::setItemsCount(int value)
{
    itemsCount = value;
}
