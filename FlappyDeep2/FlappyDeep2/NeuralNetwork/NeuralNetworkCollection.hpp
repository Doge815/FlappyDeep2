#pragma once

#include "INetwork.hpp"

#include<vector>

using namespace std;

class NeuralNetworkCollection
{
    public:
        virtual vector<INetwork*> GetNetworks() {return vector<INetwork*>();}
        virtual void Evolve() = 0;
};