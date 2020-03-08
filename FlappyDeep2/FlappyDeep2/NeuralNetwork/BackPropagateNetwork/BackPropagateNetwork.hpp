#pragma once

#define step 0.01

#include "../INetwork.hpp"
#include "../NetworkShape.hpp"

#include <vector>

using namespace std;

enum LayerType {Hidden, Input, Output};

class BackPropagateNetwork : INetwork
{
    private:
      BackPropagateLayer* Layers;

    public:
        BackPropagateNetwork(NetworkShape shape);
        void Inputs(double* values);
        double* Outputs();

        void SetFitness(double* values);
        double* GetValues();

        void Learn();
};

class BackPropagateLayer
{
    private:
        BackPropagateNetwork network;

        vector<vector<double>> Factors;
        LayerType type;
    
    public:
        BackPropagateLayer* TargetLayer;
        vector<double> Values;
        void ForwardPropagate();
        void BackPropagate();

        double Activate(double value);
        double Deactivate(double value);
};

void BackPropagateLayer::ForwardPropagate()
{
    for (int i = 0; i < Factors.size(); i++)
    {
        double accumulator = 0;

        for (int j = 0; j < Factors[0].size(); j++)
        {
            accumulator += Values[j] * Factors[j][i];
        }

        TargetLayer->Values[i] = Activate(accumulator);
    }
}

void BackPropagateLayer::BackPropagate()
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

inline double BackPropagateLayer::Activate(double value)
{
    return 0.0;
}

inline double BackPropagateLayer::Deactivate(double value)
{
    return 0.0;
}