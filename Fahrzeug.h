#pragma once
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
extern double dGlobaleZeit;

class Fahrzeug
{
private:
	// hochzaehlende Klassenvariable, um ID zu vergeben
	// definiert als static, sodass es fuer alle Instanzen dasselbe ist
	static int p_iMaxID;

protected:
	const int p_iID = 0;
	string p_sName = "";
	double p_dMaxGeschwindigkeit = 0;
	double p_dGesamtStrecke = 0;
	double p_dGesamtZeit = 0;
	double p_dZeit = 0;

public:
	// Default - Konstruktor
	Fahrzeug();
	// Konstrukor mit dem Namen
	Fahrzeug(const string sName);
	//Konstruktor mit dem Namen und der maximalen Geschwindigkeit
	Fahrzeug(const string sName, const double dMaxGeschw);
	// Destruktor
	virtual ~Fahrzeug();

	// Fahrzeug spezifische Daten ausgeben
	virtual void vAusgeben(ostream& o) const ;

	// Ueberschrift
	static void vKopf();

	// Simulationsschritt simulieren
	virtual void vSimulieren();

	// Tanke
	virtual double dTanken(double dMenge = numeric_limits<double>::infinity());

	// Geschwindigkeit
	virtual double dGeschwindigkeit() const;

	bool operator<(const Fahrzeug& pFzg) const;

	// Verbot von Copy-Konstruktor
	Fahrzeug(const Fahrzeug&) = delete;

	// Zuweisungsoperator =
	void operator=(const Fahrzeug& pFzg);
};

// Ueberladung von <<
ostream& operator<<(ostream& o, const Fahrzeug&);