#pragma once
#include "Verhalten.h"
#include "Weg.h"

class Fahren :
    public Verhalten
{
public:
    Fahren(Weg& aWeg);
    virtual ~Fahren();  
    // Maximal mögliche Fahrstrecke auf dem aktuellen Weg des Fahrzeuges - 
    // eventuell befindet sich das Fahrzeug nahe dem Wegende
    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const;
};

