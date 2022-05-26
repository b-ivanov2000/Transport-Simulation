#pragma once
#include "Verhalten.h"

class Parken :
    public Verhalten
{
private:
    double p_dStartzeitpunkt;
public:
    // Konstruktor
    Parken(Weg& aWeg, double dStartzeitpunkt);

    // Destruktor
    virtual ~Parken();

    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const override;
};

