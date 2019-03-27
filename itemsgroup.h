#ifndef ITEMSGROUP_H
#define ITEMSGROUP_H

#include <QList>
#include <QDebug>
#include "item.h"

class ItemsGroup
{
private:
    QList<Item*> items;
    int count;
public:
    ItemsGroup();
    QList<Item*> getItems() const;
    Item *getItemByName(const QString &name) const;
    void setItems(const QList<Item*> &value);
    void removeItem(Item* item);
    void addItem(Item* item);
    int getCount() const;
    void setCount();
};

#endif // ITEMSGROUP_H
