#pragma once

#include "../NeuralNetworkCollection.hpp"
#include "../NetworkShape.hpp"
#include "BackPropagateNetwork.hpp"

#include<vector>

using namespace std;

class BackPropagateNetworkCollection : NeuralNetworkCollection
{
    BackPropagateNetwork* nets;
    public:
        vector<INetwork*> GetNetworks();
        void Evolve();
};