#ifndef GAUSSRANDOMGENERATOR_H
#define GAUSSRANDOMGENERATOR_H

#include <iostream>
#include <random>

class GaussRandomGenerator
{
public:
    GaussRandomGenerator(double min, double max);
    double rand();

    double getMin() const;
    void setMin(double value);

    double getMax() const;
    void setMax(double value);

private:
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
    double min;
    double max;
};

#endif // GAUSSRANDOMGENERATOR_H
