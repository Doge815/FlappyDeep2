#pragma once

#include "INetwork.hpp"

#include<vector>

using namespace std;

class NeuralNetworkCollection
{
    public:
        virtual vector<INetwork*> GetNetworks();
        virtual void Evolve();
};