#pragma once

#include "../INetwork.hpp"
#include "../NetworkShape.hpp"
#include "BackPropagateNetworkLayer.hpp"

#include <vector>
#include <math.h>

using namespace std;

class BackPropagateNetwork : public INetwork
{
    private:

        vector<BackPropagateNetworkLayer> Layers;

    public:

        BackPropagateNetwork(NetworkShape shape);

        vector<double> Evaluate(vector<double> input) override;
        double Learn(vector<double> input, vector<double> expected);
};

BackPropagateNetwork::BackPropagateNetwork(NetworkShape shape)
{
    Layers = vector<BackPropagateNetworkLayer>();
    
    for (size_t i = 0; i < shape.GetSize().size() - 1; i++)
    {
        Layers.push_back(BackPropagateNetworkLayer(shape.GetSize()[i], shape.GetSize()[i+1]));
    }
}

vector<double> BackPropagateNetwork::Evaluate(vector<double> input)
{
    vector<double> current = input;

    for (size_t i = 0; i < Layers.size(); i++)
    {
        current = Layers[i].Evaluate(current);
    }

    return current;
}

double BackPropagateNetwork::Learn(vector<double> input, vector<double> expected)
{
    vector<vector<double>> Iout = vector<vector<double>>();
    Iout.push_back(input);
    for (size_t i = 0; i < Layers.size() ; i++)
    {
        Iout.push_back(Layers[i].Evaluate(Iout[i]));
    }

    vector<double> errorSignal = vector<double>();
    double error = 0;

    for (size_t i = 0; i < input.size(); i++)
    {
        double absoluteError = expected[i] - input[i];
        error += absoluteError * absoluteError;
        errorSignal.push_back(absoluteError);
    }

    error /= input.size();
    
    for (int i = Layers.size() - 1; i >= 0; i--)
    {
        errorSignal = Layers[i].Train(errorSignal, Iout[i], Layers[i].ActivationInverse(Iout[i+1]));
    }

    return error;
}