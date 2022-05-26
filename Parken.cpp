#include "Parken.h"
#include "Losfahren.h"
#include "Hilfsfunktionen.h"
Parken::Parken(Weg& aWeg, double dStartzeitpunkt) :
	Verhalten(aWeg), p_dStartzeitpunkt(dStartzeitpunkt)
{
}

Parken::~Parken()
{
}

// const hinzufuegen wenn fertig
double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const
{
    if (bDoublesGroesser(dGlobaleZeit, p_dStartzeitpunkt, 1e-6))
    {
        throw Losfahren(aFzg, p_rWeg);
    }
    else
    {
        return 0.0;
    }
}