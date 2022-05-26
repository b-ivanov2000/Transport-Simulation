#include "Fahrzeug.h"


// Initialisiering der hochzaehlende Variable
int Fahrzeug::p_iMaxID = 0;

Fahrzeug::Fahrzeug(): p_iID(p_iMaxID)
{
	p_iMaxID++;
	cout << "---Default-Konstruktor---" << endl;
	cout << "Erzeugtes Fahrzeug: " << endl;
	cout << "Name: " << p_sName << endl;
	cout << "ID: " << p_iID << endl;
	cout << endl;
}

Fahrzeug::Fahrzeug(const string sName) : p_sName(sName), p_iID(p_iMaxID)
{
	p_iMaxID++;
	cout << "---Konstruktor---" << endl;
	cout << "Erzeugtes Fahrzeug: " << endl;
	cout << "Name: " << p_sName << endl;
	cout << "ID: " << p_iID << endl;
	cout << endl;
}

Fahrzeug::Fahrzeug(const string sName, const double dMaxGeschw) 
	: p_sName(sName), p_dMaxGeschwindigkeit((dMaxGeschw > 0) ? dMaxGeschw : 0), p_iID(p_iMaxID)
{
	p_iMaxID++;
	cout << "---Konstruktor---" << endl;
	cout << "Erzeugtes Fahrzeug: " << endl;
	cout << "Name: " << p_sName << endl;
	cout << "ID: " << p_iID << endl;
	cout << endl;
}

Fahrzeug::~Fahrzeug()
{
	cout << "---Destruktor---" << endl;
	cout << "Geloeschtes Fahrzeug: " << endl;
	cout << "Name: " << p_sName << endl;
	cout << "ID: " << p_iID << endl;
	cout << endl;

}

void Fahrzeug::vAusgeben(ostream& o) const
{
	o.flags(ios::right);
	o << setw(2) << p_iID;
	o << setw(4) << " ";
	o.flags(ios::left);
	o << setw(14) << p_sName;
	o.flags(ios::right);
	o.setf(ios::fixed, ios::floatfield);
	o.precision(2);
	o << setw(14) << p_dMaxGeschwindigkeit << setw(17) << p_dGesamtStrecke << setw(28) << dGeschwindigkeit();
}

void Fahrzeug::vKopf()
{
	cout << resetiosflags(ios::left);
	cout << "ID" << setw(8) << "Name" << setw(24) << "Max. Geschwindigkeit" << setw(17) << "Gesamtstrecke"
		 << setw(28) << "aktuelle Geschwindigkeit" << setw(19) << "Gesamtverbrauch"  << setw(24) << "aktueller Tankinhalt" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------";
}

void Fahrzeug::vSimulieren()
{
	// if-statement ueberprueft, ob das Fahrzeug in einem Zeitschitt nur einmal sich bewegt.
	if (p_dZeit < dGlobaleZeit)
	{
		p_dGesamtStrecke += (dGlobaleZeit - p_dZeit) * dGeschwindigkeit();
		p_dGesamtZeit += dGlobaleZeit - p_dZeit;
		p_dZeit = dGlobaleZeit;
	}
}

double Fahrzeug::dTanken(double dMenge)
{
	return 0;
}

double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}

bool Fahrzeug::operator<(const Fahrzeug& pFzg) const
{
	if (this->p_dGesamtStrecke < pFzg.p_dGesamtStrecke) return true;
	else return false;
}

ostream& operator<<(ostream& o, const Fahrzeug& pFzg)
{
	pFzg.vAusgeben(o);
	return o;
}

void Fahrzeug::operator=(const Fahrzeug& pFzg)
{
	this->p_sName = pFzg.p_sName;
	this->p_dMaxGeschwindigkeit = pFzg.p_dMaxGeschwindigkeit;
}