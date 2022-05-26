#pragma once
#include "Fahrzeug.h"
class Fahrrad :
    public Fahrzeug
{
public:
    double dGeschwindigkeit() const override;

    // Konstruktor
    Fahrrad(const string sName, const double dMaxGeschw);

    // Destrukor
    virtual ~Fahrrad();
};

