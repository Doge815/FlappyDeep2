#pragma once

#define step 0.01

#include <vector>
#include <stdexcept>
#include <math.h>

using namespace std;

enum LayerType {Hidden, Input, Output};

class BackPropagateNetworkLayer
{
    private:

        vector<vector<double>> Factors;
        LayerType type;
    
    public:
        BackPropagateNetworkLayer* TargetLayer;

        BackPropagateNetworkLayer(LayerType t, int size, int j);
        vector<double> ForwardPropagate(vector<double> val);
        vector<double> BackPropagate(vector<double> val);

        double Activate(double value);
        double Deactivate(double value);
};

BackPropagateNetworkLayer::BackPropagateNetworkLayer(LayerType t, int size, int j)
{
    type = t;

    Factors = vector<vector<double>>();
    for (size_t i = 0; i < size; i++)
    {
        Factors.push_back(vector<double>());
        if(t == LayerType::Input)
        {
            Factors[i].push_back(1);
        }
        else
        {
            for (size_t u = 0; u < j; u++)
            {
                Factors[i].push_back((double) rand() / (RAND_MAX)*2-1);
            }
        }
    }
    
}

vector<double> BackPropagateNetworkLayer::ForwardPropagate(vector<double> val)
{
    vector<double> v = vector<double>();
    for (int i = 0; i < Factors.size(); i++)
    {
        double accumulator = 0;

        for (int j = 0; j < Factors[0].size(); j++)
        {
            accumulator += val[j] * Factors[j][i];
        }

        v.push_back(accumulator);
    }
    if(type == LayerType::Output) return v;
    return TargetLayer->ForwardPropagate(v);
}

vector<double> BackPropagateNetworkLayer::BackPropagate(vector<double> val)
{
    vector<double> v = vector<double>();
    for (int i = 0; i < Factors.size(); i++)
    {
        double accumulator = 0;

        for (int j = 0; j < Factors[0].size(); j++)
        {
            double value = Deactivate(val[j] * Factors[i][j]);
            accumulator += value;
            Factors[i][j] += value * step;
        }

        v[i] = accumulator;
        v.push_back(accumulator);
    }
    return v;
}

inline double BackPropagateNetworkLayer::Activate(double value)
{
    return fmaxf64(0, value);
}

inline double BackPropagateNetworkLayer::Deactivate(double value)
{
    return fminf64(0, value);
}