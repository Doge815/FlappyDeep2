#pragma once

class INetwork
{
    public:
        virtual void Inputs(double* values);
        virtual double* Outputs();

        virtual void SetFitness(double* values);
        virtual double* GetValues();
};