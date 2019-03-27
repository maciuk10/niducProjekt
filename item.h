#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <QString>

class Item {
private:
    QString name;
    QString type;
    double mtbf;
    double mttr;
    double mttf;
    double availability;
    QString distribution;
public:
    Item(QString name, QString type, double mtbf, double mttr);
    QString getName() const;
    void setName(const QString &value);
    QString getType() const;
    void setType(const QString &value);
    double getMtbf() const;
    void setMtbf(double value);
    double getMttr() const;
    void setMttr(double value);
    double getMttf() const;
    void setMttf(double value);
    double getAvailability() const;
    void setAvailability(int time);
    QString getDistribution() const;
    void setDistribution(const QString &value);
};

#endif // ITEM_H
