#pragma once
#include "Fahrzeug.h"
class Fahrrad :
    public Fahrzeug
{
public:
    double dGeschwindigkeit() const override;

    // Konstruktor
    Fahrrad(const string sName, const double dMaxGeschw);

    // Default-Konstruktor
    Fahrrad();

    // Destruktor
    virtual ~Fahrrad();

    // Zeichnung
    void vZeichnen(const Weg&)const override;
};

