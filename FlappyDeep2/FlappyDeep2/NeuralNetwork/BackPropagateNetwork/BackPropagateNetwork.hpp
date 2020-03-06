#pragma once

#include "../INetwork.hpp"
#include "../NetworkShape.hpp"

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

        double* Values;
        double** Factors;
        LayerType type;
    
    public:
        void ForwardPropagate();
        void BackPropagate();
};