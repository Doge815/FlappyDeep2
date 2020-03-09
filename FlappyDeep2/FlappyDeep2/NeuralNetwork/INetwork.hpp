#pragma once

#include <vector>

using namespace std;

class INetwork
{
    public:
        virtual vector<double> Calculate(vector<double> values);

        virtual void SetFitness(vector<double> values);
        virtual vector<double> GetValues();
};