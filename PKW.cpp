#include "PKW.h"
#include "Verhalten.h"
#include "Hilfsfunktionen.h"

PKW::PKW(string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen) :
	Fahrzeug(sName, dMaxGeschwindigkeit), p_dVerbrauch(dVerbrauch), p_dTankvolumen(dTankvolumen), p_dTankinhalt(dTankvolumen / 2)
{
	cout << "Typ des erstellten Fahrzeugs: PKW" << endl;
	cout << endl;
}

PKW::PKW():Fahrzeug()
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
	if (dMenge <= 0.0)
	{
		return 0.0;
	}
	else if (bDoublesGroesser(dFrei, dMenge, 1e-6))
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

	if (p_dTankinhalt <= 0.0)
	{
		// passiert nichts
		p_dZeit = dGlobaleZeit;
	}
	else
	{
		double dAlteStrecke = p_dAbschnittStrecke;
		Fahrzeug::vSimulieren();
		double dNeueStrecke = p_dAbschnittStrecke;
		double dVerbraucht = (dNeueStrecke - dAlteStrecke) * p_dVerbrauch / 100.0;
		if (bDoublesKleiner(p_dTankinhalt, dVerbraucht, 1e-6))
		{
			p_dTankinhalt = 0.0;
		}
		else
		{
			p_dTankinhalt -= dVerbraucht;
		}
	}
}

void PKW::vAusgeben(ostream& o) const
{
	double dGesamtverbrauch = p_dGesamtStrecke * p_dVerbrauch / 100.0;
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

double PKW::dGeschwindigkeit() const
{
	if (p_pVerhalten != nullptr)
	{
		// prueft ob die maximale Geschwindigkeit das Limit ueberschreitet
		if (bDoublesGroesser(p_dMaxGeschwindigkeit, p_pVerhalten->dGetGeschwindigkeitslimit(), 1e-6)) return p_pVerhalten->dGetGeschwindigkeitslimit();
		else return p_dMaxGeschwindigkeit;
	}
	else
	{
		return p_dMaxGeschwindigkeit;
	}
}

void PKW::vZeichnen(const Weg& aWeg) const
{
	double dRelPosition = p_dAbschnittStrecke / aWeg.dGetLaenge();
	if (dRelPosition < 0.0) dRelPosition = 0.0;
	if (dRelPosition > 1.0) dRelPosition = 1.0;
	bZeichnePKW(p_sName, aWeg.sGetName(), dRelPosition, dGeschwindigkeit(), p_dTankinhalt);
}

bool PKW::bUberholbar() const
{
	if (this->p_dTankinhalt > 0.0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void PKW::vEinlesen(istream& in)
{
	Fahrzeug::vEinlesen(in);
	in >> p_dVerbrauch;
	in >> p_dTankvolumen;
	p_dTankinhalt = p_dTankvolumen / 2;
}