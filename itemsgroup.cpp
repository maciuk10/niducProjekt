#include "itemsgroup.h"

QList<Item*> ItemsGroup::getItems() const
{
    return items;
}

Item *ItemsGroup::getItemByName(const QString &name) const {
    foreach(Item* item, items){
        if(item->getName() == name){
            return item;
        }
    }
    return nullptr;
}

void ItemsGroup::setItems(const QList<Item *> &value) {
    items = value;
    setCount();
}

void ItemsGroup::addItem(Item *item) {
    items.append(item);
    setCount();
}

int ItemsGroup::getCount() const {
    return count;
}

void ItemsGroup::setCount() {
    count = items.length();
}

ItemsGroup::ItemsGroup() {
    count = 0;
}
