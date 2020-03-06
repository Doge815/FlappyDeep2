#pragma once

#include "../NeuralNetworkCollection.hpp"
#include "../NetworkShape.hpp"
#include "BackPropagateNetwork.hpp"

#include<vector>
#include<cstdlib>

using namespace std;

class BackPropagateNetworkCollection : NeuralNetworkCollection
{
    BackPropagateNetwork* nets;
    int amountOfNetworks;
    public:
        BackPropagateNetworkCollection(int amount, NetworkShape shape);
        vector<INetwork*> GetNetworks();
        void Evolve();
};

BackPropagateNetworkCollection::BackPropagateNetworkCollection(int amount, NetworkShape shape)
{
    nets = (BackPropagateNetwork*)malloc(sizeof(amount));
    for(int i = 0; i < amount; i++)
    {
        nets[i] = BackPropagateNetwork(shape);
    }
}

void BackPropagateNetworkCollection::Evolve()
{
    for (size_t i = 0; i < amountOfNetworks; i++)
    {
        nets[i].Learn();
    }
    
}