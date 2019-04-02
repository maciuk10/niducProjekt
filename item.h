#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <QString>
#include <cmath>

class Item {
private:
    QString name;
    QString type;
    double mtbf;
    double mttr;
    double mttf;
    double availability;
    QString distribution;
    int year;
    bool switched;
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
    double calcMttf();
    double floatRound(double floatMin, double floatMax);
    QString getDistribution() const;
    void setDistribution(const QString &value);
    int getYear() const;
    void setYear(int value);
    bool getSwitched() const;
    void setSwitched(bool value);
};

#endif // ITEM_H
