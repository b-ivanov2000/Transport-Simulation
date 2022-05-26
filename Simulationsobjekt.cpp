#include "Simulationsobjekt.h"
#include <iomanip>

// Initialisiering der hochzaehlende Variable
int Simulationsobjekt::p_iMaxID = 0;

Simulationsobjekt::Simulationsobjekt()
	: p_iID(p_iMaxID++)
{
	p_iMaxID++;
	cout << "---Default-Konstruktor---" << endl;
	cout << "Erzeugtes Simulationsobjekt: " << endl;
	cout << "Name: " << p_sName << endl;
	cout << "ID: " << p_iID << endl;
	cout << endl;
}

Simulationsobjekt::Simulationsobjekt(const string sName) : p_sName(sName), p_iID(p_iMaxID)
{
	p_iMaxID++;
	cout << "---Konstruktor---" << endl;
	cout << "Erzeugtes Simulationsobjekt: " << endl;
	cout << "Name: " << p_sName << endl;
	cout << "ID: " << p_iID << endl;
	cout << endl;
}

Simulationsobjekt::~Simulationsobjekt()
{
	cout << "---Destruktor---" << endl;
	cout << "Geloeschtes Simulationsobjekt: " << endl;
	cout << "Name: " << p_sName << endl;
	cout << "ID: " << p_iID << endl;
	cout << endl;
}

void Simulationsobjekt::vAusgeben(ostream& o) const
{
	o.flags(ios::right);
	o << setw(4) << p_iID;
	o << setw(2) << " ";
	o.flags(ios::left);
	o << setw(12) << p_sName;
}

void Simulationsobjekt::vSimulieren()
{
}

bool Simulationsobjekt::operator==(const Simulationsobjekt& s2)
{
	return (this->p_iID == s2.p_iID) ? true : false;
}

string Simulationsobjekt::sGetName() const
{
	return p_sName;
}

void Simulationsobjekt::vEinlesen(istream& i)
{
	// Prueft ob der Name benutzt wird
	if (p_sName != "")
	{
		throw runtime_error("Der Name wird schon benutzt.");
	}
	i >> p_sName;
}


ostream& operator<<(ostream& o, const Simulationsobjekt& SimObj)
{
	SimObj.vAusgeben(o);
	return o;
}
istream& operator>>(istream& i, Simulationsobjekt& SimObj)
{
	SimObj.vEinlesen(i);
	return i;
}