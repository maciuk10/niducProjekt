#include "item.h"

QString Item::getDistribution() const
{
    return distribution;
}

void Item::setDistribution(const QString &value)
{
    distribution = value;
}

Item::Item(QString name, QString type, double mtbf, double mttr) {
    this->name = name;
    this->type = type;
    this->mtbf = mtbf;
    this->mttr = mttr;
    this->mttf = mtbf - mttr;
    this->distribution = "CONST";
}

QString Item::getName() const {
    return name;
}

void Item::setName(const QString &value)
{
    name = value;
}

QString Item::getType() const
{
    return type;
}

void Item::setType(const QString &value)
{
    type = value;
}

double Item::getMtbf() const
{
    return mtbf;
}

void Item::setMtbf(double value)
{
    mtbf = value;
}

double Item::getMttr() const
{
    return mttr;
}

void Item::setMttr(double value)
{
    mttr = value;
}

double Item::getMttf() const
{
    return mttf;
}

void Item::setMttf(double value)
{
    mttf = value;
}

double Item::getAvailability() const
{
    return availability;
}

void Item::setAvailability(int time) {
    if(getDistribution() == ""){
        availability = mttf / (mttf + mttr);
    }else {
        if(getDistribution() == "Rozkład Normalny"){

        }else if (getDistribution() == "Rozkład Weibulla"){

        }else if (getDistribution() == "Rozkład Wykładniczy") {

        }else {
            availability = mttf / (mttf + mttr);
        }
    }
}
