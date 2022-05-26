#pragma once
#include "Weg.h"
#include "Fahrzeug.h"

class Weg;
class Fahrzeug;

class Verhalten
{
protected:
	Weg& p_rWeg;
public:
	// Konstruktor mit dem Weg
	Verhalten(Weg& rWeg);

	// Destruktor
	virtual ~Verhalten();

	// Maximal mögliche Fahrstrecke auf dem aktuellen Weg des Fahrzeuges - 
	// eventuell befindet sich das Fahrzeug nahe dem Wegende
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const = 0;

	// Getter fuer die Geschwindigkeit des Wegs
	double dGetGeschwindigkeitslimit();
};

