#include "Fahren.h"
#include "Streckenende.h"
#include "Hilfsfunktionen.h"
#include <cmath>
Fahren::Fahren(Weg& aWeg)
    : Verhalten(aWeg)
{
}

Fahren::~Fahren()
{
}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const
{
	// Schranke des Wegs, auf dem gefahren ist - falls keine Schranke => Weglaenge
	double  dSchranke = this->p_rWeg.dGetVirtuelleSchranke();

	// Das Fahrzeug versucht diese Strecke zurueckzulegen
	double dFahrstrecke = aFzg.dGeschwindigkeit() * dZeitIntervall;

	// prueft ob Fahrzeug schon am Ende ist	
	if (bDoublesGroesser(p_rWeg.dGetLaenge(), aFzg.dGetAbschnittstrecke(), 1e-6))
	{
		// prueft ob Fahrzeug eine Schranke hat
		if (bDoublesKleiner(p_rWeg.dGetVirtuelleSchranke(), aFzg.dGetAbschnittstrecke() + dFahrstrecke, 1e-6))
		{
			dFahrstrecke = dSchranke - aFzg.dGetAbschnittstrecke();
			return dFahrstrecke;
		}
		else
		{
			// Schranke bekommt den Wert der Fahrstrecke, die das Fahrzeug zuruecklegen kann
			// So werden die Schranken fuer alle Fahrzeuge bestimmt
			p_rWeg.vSetVirtuelleSchranke(aFzg.dGetAbschnittstrecke() + dFahrstrecke);
			return dFahrstrecke;
		}
	}
	else
	{
		throw Streckenende(aFzg, p_rWeg);
	}
}
