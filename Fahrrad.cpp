#include "Fahrrad.h"
#include <cmath>
double Fahrrad::dGeschwindigkeit() const
{
	double dGeschw = p_dMaxGeschwindigkeit * pow(0.9, floor(p_dGesamtStrecke / 20.0));
	if (dGeschw <= 12.0) dGeschw = 12.0;
	return dGeschw;
}

Fahrrad::Fahrrad(const string sName, const double dMaxGeschw) :
	Fahrzeug(sName, dMaxGeschw)
{
	cout << "Typ des erstellten Fahrzeugs: Fahrrad" << endl;
	cout << endl;
}

Fahrrad::Fahrrad() : Fahrzeug()
{
	cout << "Typ des erstellten Fahrzeugs: Fahrrad" << endl;
	cout << endl;
}


Fahrrad::~Fahrrad()
{
}

void Fahrrad::vZeichnen(const Weg& aWeg) const
{
	double dRelPosition = p_dAbschnittStrecke / aWeg.dGetLaenge();
	if (dRelPosition < 0.0) dRelPosition = 0.0;
	if (dRelPosition > 1.0) dRelPosition = 1.0;
	bZeichneFahrrad(p_sName, aWeg.sGetName(), dRelPosition, dGeschwindigkeit());
}

