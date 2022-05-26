#include "Fahrrad.h"
#include <cmath>
double Fahrrad::dGeschwindigkeit() const
{
	double dGeschw = p_dMaxGeschwindigkeit * pow(0.9, floor(p_dGesamtStrecke / 20));
	if (dGeschw <= 12) dGeschw = 12;
	return dGeschw;
}

Fahrrad::Fahrrad(const string sName, const double dMaxGeschw) :
	Fahrzeug(sName, dMaxGeschw)
{
	cout << "Typ des erstellten Fahrzeugs: Fahrrad" << endl;
	cout << endl;
}

Fahrrad::~Fahrrad()
{
}