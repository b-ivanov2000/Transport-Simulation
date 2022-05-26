#include "Fahrzeug.h"
#include "Weg.h"
#include "Verhalten.h"
#include "Parken.h"
#include "Fahren.h"
#include "Hilfsfunktionen.h"

Fahrzeug::Fahrzeug(): Simulationsobjekt()
{
	cout << "Typ des Simulationsobjektes: Fahrzeug" << endl;
	cout << endl;
}

Fahrzeug::Fahrzeug(const string sName) : Simulationsobjekt(sName)
{
	cout << "Typ des Simulationsobjektes: Fahrzeug" << endl;
	cout << endl;
}

Fahrzeug::Fahrzeug(const string sName, const double dMaxGeschw) 
	: Simulationsobjekt(sName), p_dMaxGeschwindigkeit((dMaxGeschw > 0) ? dMaxGeschw : 0)
{
	cout << "Typ des Simulationsobjektes: Fahrzeug" << endl;
	cout << endl;
}

Fahrzeug::~Fahrzeug()
{
}

void Fahrzeug::vAusgeben(ostream& o) const
{
	Simulationsobjekt::vAusgeben(o);
	o.flags(ios::right);
	o.setf(ios::fixed, ios::floatfield);
	o.precision(2);
	o << setw(16) << p_dMaxGeschwindigkeit << setw(17) << p_dGesamtStrecke << setw(28) << dGeschwindigkeit();
}

void Fahrzeug::vKopf()
{
	cout << resetiosflags(ios::left);
	cout << setw(4) << "ID" << setw(6) << "Name" << setw(24) << "Max. Geschwindigkeit" << setw(17) << "Gesamtstrecke"
		<< setw(28) << "aktuelle Geschwindigkeit" << setw(19) << "Gesamtverbrauch" << setw(24) << "aktueller Tankinhalt" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------";
	cout << endl;
}

void Fahrzeug::vSimulieren()
{
	// if-statement ueberprueft, ob das Fahrzeug in einem Zeitschitt nur einmal sich bewegt.
	if (bDoublesKleiner(p_dZeit, dGlobaleZeit, 1e-6))
	{
		double dFahrzeit = dGlobaleZeit - p_dZeit;
		if (p_pVerhalten != nullptr)
		{

			double dFahrstrecke = p_pVerhalten->dStrecke(*this, dFahrzeit);

			// Aktualisation der Strecke auf dem aktuellen Weg
			p_dAbschnittStrecke += dFahrstrecke;
			// Aktualisation der gesamte Strecke
			p_dGesamtStrecke += dFahrstrecke;

		}
		else
		{
			p_dGesamtStrecke += dFahrzeit * dGeschwindigkeit();
		}
		p_dGesamtZeit += dFahrzeit;
		// Aktualisation der p_dZeit
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

bool Fahrzeug::operator<(const Fahrzeug& aFzg) const
{
	if (bDoublesKleiner(this->p_dGesamtStrecke, aFzg.p_dGesamtStrecke, 1e-6)) return true;
	else return false;
}

void Fahrzeug::operator=(const Fahrzeug& aFzg)
{
	this->p_sName = aFzg.p_sName;
	this->p_dMaxGeschwindigkeit = aFzg.p_dMaxGeschwindigkeit;
}

// fuer fahrende Fahrzeuge
void Fahrzeug::vNeueStrecke(Weg& aWeg)
{
	// So wird die alte Instanz geloescht
	p_pVerhalten = make_unique<Fahren>(aWeg);

	// Neuer Weg => die Strecke auf diesem Weg ist 0
	this->p_dAbschnittStrecke = 0; 

	// Aktualisation der Zeit
	p_dZeit = dGlobaleZeit;
}

// fuer geparkte Fahrzeuge
void Fahrzeug::vNeueStrecke(Weg& aWeg, double dStartzeitpunkt)
{
	// So wird die alte Instanz geloescht
	p_pVerhalten = make_unique<Parken>(aWeg, dStartzeitpunkt);

	// Neuer Weg => die Strecke auf diesem Weg ist 0
	this->p_dAbschnittStrecke = 0.0;

	// Aktualisation der Zeit
	p_dZeit = dGlobaleZeit;
}

double Fahrzeug::dGetAbschnittstrecke() const
{
	return p_dAbschnittStrecke;
}

void Fahrzeug::vZeichnen(const Weg& aWeg) const
{
}

bool Fahrzeug::bUberholbar() const
{
	// default ist false - damit Fahrraeder das direkt benutzen koennen
	return false;
}


void Fahrzeug::vEinlesen(istream& in)
{
	Simulationsobjekt::vEinlesen(in);
	in >> p_dMaxGeschwindigkeit;
}