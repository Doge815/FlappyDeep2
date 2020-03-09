#pragma once

#define step 0.01

#include <vector>
#include <stdexcept>

using namespace std;

enum LayerType {Hidden, Input, Output};

class BackPropagateNetworkLayer
{
    private:

        vector<vector<double>> Factors;
        vector<double> Values;
    
    public:
        BackPropagateNetworkLayer* TargetLayer;
        LayerType type;

        vector<double> ForwardPropagate(vector<double> val);
        void BackPropagate();

        double Activate(double value);
        double Deactivate(double value);
};

vector<double> BackPropagateNetworkLayer::ForwardPropagate(vector<double> val)
{
    vector<double> v = vector<double>();
    for (int i = 0; i < Factors.size(); i++)
    {
        double accumulator = 0;

        for (int j = 0; j < Factors[0].size(); j++)
        {
            accumulator += Values[j] * Factors[j][i];
        }

        v.push_back(accumulator);
    }
    if(type == LayerType::Output) return v;
    return TargetLayer->ForwardPropagate(v);
}

void BackPropagateNetworkLayer::BackPropagate()
{
    for (int i = 0; i < Factors.size(); i++)
    {
        double accumulator = 0;

        for (int j = 0; j < Factors[0].size(); j++)
        {
            double value = Deactivate(TargetLayer->Values[j] * Factors[i][j]);
            accumulator += value;
            Factors[i][j] += value * step;
        }

        Values[i] = accumulator;
    }
}

inline double BackPropagateNetworkLayer::Activate(double value)
{
    return 0.0;
}

inline double BackPropagateNetworkLayer::Deactivate(double value)
{
    return 0.0;
}