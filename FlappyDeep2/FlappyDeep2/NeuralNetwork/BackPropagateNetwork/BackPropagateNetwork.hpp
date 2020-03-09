#pragma once

#include "../INetwork.hpp"
#include "../NetworkShape.hpp"
#include "BackPropagateNetworkLayer.hpp"

#include <vector>

using namespace std;

class BackPropagateNetwork : INetwork
{
    private:
        vector<BackPropagateNetworkLayer> Layers;
        vector<double> Fitness;

    public:
        BackPropagateNetwork(NetworkShape shape);

        vector<double> Calculate(vector<double> values);

        void SetFitness(vector<double> values);

        void Learn();
};

BackPropagateNetwork::BackPropagateNetwork(NetworkShape shape)
{
    Layers = vector<BackPropagateNetworkLayer>();
    for (size_t i = 0; i < shape.GetSize().size(); i++)
    {
        Layers.push_back(BackPropagateNetworkLayer());
    }

    for (size_t i = 0; i < Layers.size()-1; i++)
    {
        Layers[i].TargetLayer = &Layers[i+1];
        Layers[i].type = LayerType::Hidden;
    }

    Layers[0].type = LayerType::Input;
    Layers[Layers.size() - 1].type = LayerType::Output;
    
    
}

vector<double> BackPropagateNetwork::Calculate(vector<double> values)
{
    return Layers[0].ForwardPropagate(values);
}

void BackPropagateNetwork::SetFitness(vector<double> values)
{
    Fitness = values;
}

void BackPropagateNetwork::Learn()
{
    for (int i = Layers.size() - 2; i >= 0; i--)
    {
        Layers[i].BackPropagate();
    }
}