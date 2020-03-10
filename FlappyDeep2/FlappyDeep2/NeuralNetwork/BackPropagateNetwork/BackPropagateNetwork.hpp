#pragma once

#include "../INetwork.hpp"
#include "../NetworkShape.hpp"
#include "BackPropagateNetworkLayer.hpp"

#include <vector>

using namespace std;

class BackPropagateNetwork : public INetwork
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
    
    Layers.push_back(BackPropagateNetworkLayer(LayerType::Input, shape.GetSize()[0], 0));

    for (size_t i = 1; i < shape.GetSize().size() - 1; i++)
    {
        Layers.push_back(BackPropagateNetworkLayer(LayerType::Hidden, shape.GetSize()[i], shape.GetSize()[i-1]));
    }

    Layers.push_back(BackPropagateNetworkLayer(LayerType::Output, shape.GetSize()[shape.GetSize().size()-1], shape.GetSize()[shape.GetSize().size()-2]));
    
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
    vector<double> val = Fitness;
    for (int i = Layers.size() - 2; i >= 0; i--)
    {
        val = Layers[i].BackPropagate(val);
    }
}