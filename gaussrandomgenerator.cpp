#include "gaussrandomgenerator.h"

GaussRandomGenerator::GaussRandomGenerator(double min, double max) :
    distribution((min+max) / 2, (max - min) / 6),
    min(min),
    max(max)
{}

double GaussRandomGenerator::rand() {
    while(true){
        double number = this->distribution(generator);
        if(number >= this->min && number <= this->max){
            return number;
        }
    }
}

double GaussRandomGenerator::getMin() const
{
    return min;
}

void GaussRandomGenerator::setMin(double value)
{
    min = value;
    distribution = std::normal_distribution<double>((max+min)/2, (max - min)/6);
}

double GaussRandomGenerator::getMax() const
{
    return max;
}

void GaussRandomGenerator::setMax(double value)
{
    max = value;
    distribution = std::normal_distribution<double>((max+min)/2, (max - min)/6);
}
