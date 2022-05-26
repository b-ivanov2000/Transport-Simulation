#include "Losfahren.h"

Losfahren::Losfahren(Fahrzeug& aFzg, Weg& aWeg) :
	Fahrausnahme(aFzg, aWeg)
{
}

Losfahren::~Losfahren()
{
}

void Losfahren::vBearbeiten()
{
	cout << "Ausnahme: Losfahren" << endl;
	cout << "Fahrzeug " << p_aFzg.sGetName() << " setzt sich in Bewegung auf dem Weg " << p_aWeg.sGetName() << endl;
	cout << "Startzeit: " << dGlobaleZeit << endl;
	
	// Losfahren
	//p_aFzg.vNeueStrecke(p_aWeg);

	p_aWeg.vAnnahme(p_aWeg.pAbgabe(p_aFzg));
}