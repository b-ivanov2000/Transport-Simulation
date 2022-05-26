#include "Streckenende.h"


Streckenende::Streckenende(Fahrzeug& aFzg, Weg& aWeg) :
	Fahrausnahme(aFzg, aWeg)
{
}

Streckenende::~Streckenende()
{
}

void Streckenende::vBearbeiten()
{
	cout << "Ausnahme: Streckenende" << endl;
	cout << "Fahrzeug " << p_aFzg.sGetName() << " hat das Ende des Weges " << p_aWeg.sGetName() << " erreicht" << endl;
	cout << "Zeitpunkt: " << dGlobaleZeit << endl;
	Kreuzung* pZielKreuzung = &(p_aWeg.pGetZielkreuzung());
	if (pZielKreuzung != nullptr)
	{
		Weg& pNeuerWeg = pZielKreuzung->pZufaelligerWeg(p_aWeg);
		pZielKreuzung->vTanken(p_aFzg);
		pNeuerWeg.vAnnahme(p_aWeg.pAbgabe(p_aFzg));
		cout << "ZEIT       : " << dGlobaleZeit << endl;
		cout << "KREUZUNG   : " << pZielKreuzung->sGetName() << " Inhalt der Tankstelle: " << pZielKreuzung->dGetTankstelle() << endl;
		cout << "WECHSEL    : " << p_aWeg.sGetName() << " -> " << pNeuerWeg.sGetName() << endl;
		cout << "FAHRZEUG   : " << endl;
		Fahrzeug::vKopf();
		cout << endl;
		cout << p_aFzg << endl;
	}
}