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
        vector<double> Input;
        vector<double> Sum;
        vector<double> Output;
        LayerType type;
    
    public:
        BackPropagateNetworkLayer* TargetLayer;
        BackPropagateNetworkLayer* InputLayer;

        BackPropagateNetworkLayer(LayerType t, int size, int j);
        vector<double> ForwardPropagate(vector<double> val);
        vector<double> BackPropagate(vector<double> val);

        vector<double> Activate(vector<double> value);
        vector<double> Deactivate(vector<double> value);
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
    Input = val;
    Sum = vector<double>();

    for (int i = 0; i < Input.size(); i++)
    {
        double accumulator = 0;

        for (int j = 0; j < Factors[i].size(); j++)
        {
            accumulator += val[j] * Factors[j][i];
        }

        Sum.push_back(accumulator);
    }

    Output = Activate(Sum);

    if(type == LayerType::Output) return Output;
    return TargetLayer->ForwardPropagate(Output);
}

vector<double> BackPropagateNetworkLayer::BackPropagate(vector<double> y)
{
    //Todo: size check
    double error = 0;
    for(int i = 0; i < y.size(); i++)
    {
        error -= y[i]*std::log10(Output[i]) + (1 - y[i] * std::log10(1 - Output[i]));
    }

    vector<double> dEdOout = vector<double>();
    for(int i = 0; i < Output.size(); i++)
    {
        dEdOout.push_back(-1 * (( y[i] * (1 / Output[i]) + (1 - y[i]) * (1/(1- Output[i])))) ); //todo: Check me
    }

    vector<double> dOoutdOin = vector<double>();

    double s = 0;

    for(int i = 0; i < Output.size(); i++)
    {
        s += exp(Input[i]);
    }

    s = std::pow(s, 2);

    for(int i = 0; i < Output.size(); i++)
    {
        double f = 0;
        for (size_t u = 0; u < Output.size(); i++)
        {
            if(i != u)
            {
                f += exp(Input[u]);
            }
        }
        f *= exp(Input[i]);
         
        dOoutdOin.push_back( f / s );
    }

    vector<double> dOindW = vector<double>();

    for (size_t i = 0; i < InputLayer->Output.size(); i++)
    {
        dOindW.push_back(InputLayer->Output[i]);
    }

    vector<vector<double>> dW = vector<vector<double>>();
    {
        dW.push_back(vector<double>());
        for (size_t i = 0; i < Factors.size(); i++)
        {
            for (size_t u = 0; u < Factors[i].size(); u++)
            {
                dW[i].push_back(dOindW[u] * dOoutdOin[i] * dEdOout[i]);
                Factors[i][u] -= step * dW[i][u];
            }
        }
    }
    
}

vector<double> BackPropagateNetworkLayer::Activate(vector<double> value)
{
    vector<double> output = vector<double>();
    for(int i = 0; i < value.size(); i++)
    {
        output.push_back(fmaxf64(0, value[i]));
    }
    return output;
}

vector<double> BackPropagateNetworkLayer::Deactivate(vector<double> value)
{
    vector<double> output = vector<double>();
    for(int i = 0; i < value.size(); i++)
    {
        output.push_back(value[i] > 0 ? 1 : 0);
    }
    return output;
}