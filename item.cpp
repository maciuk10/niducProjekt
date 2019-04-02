#include "item.h"

QString Item::getDistribution() const
{
    return distribution;
}

double Item::floatRound(double floatMin, double floatMax) {
    double f = (double)rand() / RAND_MAX;
    return floatMin + f * (floatMax - floatMin);
}

void Item::setDistribution(const QString &value){
    distribution = value;
}

int Item::getYear() const
{
    return year;
}

void Item::setYear(int value)
{
    year = value;
}

bool Item::getSwitched() const
{
    return switched;
}

void Item::setSwitched(bool value)
{
    switched = value;
}

Item::Item(QString name, QString type, double mtbf, double mttr) {
    this->name = name;
    this->type = type;
    this->mtbf = mtbf;
    this->mttr = mttr;
    this->mttf = calcMttf();
    this->distribution = "";
    this->year = 0;
    this->switched = false;
}

QString Item::getName() const {
    return name;
}

void Item::setName(const QString &value) {
    name = value;
}

QString Item::getType() const {
    return type;
}

void Item::setType(const QString &value) {
    type = value;
}

double Item::getMtbf() const {
    return mtbf;
}

void Item::setMtbf(double value) {
    mtbf = value;
}

double Item::getMttr() const {
    return mttr;
}

void Item::setMttr(double value) {
    mttr = value;
}

double Item::getMttf() const {
    return mttf;
}

void Item::setMttf(double value) {
    mttf = value;
}

double Item::calcMttf() {
    if(this->type == "HARD_DRIVES" || this->type == "SWITCHES"){
        mttf = (floatRound(0.70, 0.78)) * (mtbf - mttr);
    }else if (this->type == "POWER_SUPPLIES" || this->type == "COOLING_SYSTEMS"){
        mttf = (floatRound(0.87, 0.92)) * (mtbf - mttr);
    }else if (this->type == "FIREWALLS"){
        mttf = (floatRound(0.85, 0.91)) * (mtbf - mttr);
    }else if (this->type == "ROUTERS"){
        mttf = (floatRound(0.91, 0.93)) * (mtbf - mttr);
    }else if (this->type == "POWER_UNITS") {
        mttf = (floatRound(0.97, 0.98)) * (mtbf - mttr);
    }else if (this->type == "CONNECTIONS") {
        mttf = (floatRound(0.91, 0.96)) * (mtbf - mttr);
    }else {
        mttf = mtbf - mttr;
    }
    return mttf;
}

double Item::getAvailability() const {
    return availability;
}

void Item::setAvailability(int time) {
    availability = mttf / mtbf;
    if(switched){
        time = this->getYear();
        this->setYear(this->getYear()+1);
    }
    if(getDistribution() == "Rozkład Wykładniczy"){
        double lambda = availability / 125.0;
        availability = availability * pow(M_E, (-1)*lambda*time);
    }
    if(getDistribution() == "Rozkład Weibulla"){
        double lambda = 0.00606;
        double beta = 0.7;
        availability = availability * pow(M_E, (-1)*pow(lambda*time, beta));
    }
}
