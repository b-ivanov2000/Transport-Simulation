#include "PKW.h"

PKW::PKW(string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen) :
	Fahrzeug(sName, dMaxGeschwindigkeit), p_dVerbrauch(dVerbrauch), p_dTankvolumen(dTankvolumen), p_dTankinhalt(dTankvolumen / 2)
{
	cout << "Typ des erstellten Fahrzeugs: PKW" << endl;
	cout << endl;
}

PKW::~PKW()
{
}

double PKW::dTanken(double dMenge)
{
	double dFrei = p_dTankvolumen - p_dTankinhalt;
	if (dMenge <= 0)
	{
		return 0;
	}
	else if (dFrei >= dMenge)
	{
		p_dTankinhalt += dMenge;
		return dMenge;
	}
	else
	{
		p_dTankinhalt = p_dTankvolumen;
		return dFrei;
	}
}

void PKW::vSimulieren()
{
	// verbraucht in einem Schritt
	double dVerbraucht = (dGlobaleZeit - p_dZeit) * p_dMaxGeschwindigkeit * p_dVerbrauch / 100;

	if (p_dTankinhalt <= 0)
	{
		// passiert nichts
		p_dZeit = dGlobaleZeit;
	}
	else
	{
		Fahrzeug::vSimulieren();
		if (p_dTankinhalt - dVerbraucht <= 0)
		{
			p_dTankinhalt = 0;
		}
		else
		{
			p_dTankinhalt -= dVerbraucht;
		}
	}
}

void PKW::vAusgeben(ostream& o) const
{
	double dGesamtverbrauch = p_dGesamtStrecke * p_dVerbrauch / 100;
	Fahrzeug::vAusgeben(o);
	o << setw(19) << dGesamtverbrauch << setw(24) << p_dTankinhalt;
}

void PKW::operator=(const PKW& pkw)
{
	this->p_sName = pkw.p_sName;
	this->p_dMaxGeschwindigkeit = pkw.p_dMaxGeschwindigkeit;
	this->p_dVerbrauch = pkw.p_dVerbrauch;
	this->p_dTankvolumen = pkw.p_dTankvolumen;
}