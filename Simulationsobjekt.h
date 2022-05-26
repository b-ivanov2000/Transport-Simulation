#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

extern double dGlobaleZeit;

class Simulationsobjekt
{
private:
	// hochzaehlende Klassenvariable, um ID zu vergeben
	// definiert als static, sodass es fuer alle Instanzen dasselbe ist
	static int p_iMaxID;

protected:
	const int p_iID = 0;
	string p_sName = "";
	double p_dZeit = 0;

public:
	// Default - Konstruktor
	Simulationsobjekt();

	// Konstrukor mit dem Namen
	Simulationsobjekt(const string sName);

	// Simulationsobjekt spezifische Daten ausgeben
	virtual void vAusgeben(ostream& o) const = 0;

	// Destruktor
	virtual ~Simulationsobjekt();

	// Verbot von Copy-Konstruktor
	Simulationsobjekt(const Simulationsobjekt&) = delete;

	// Vergleichsoperator ==
	bool operator==(const Simulationsobjekt& s2);

	// Simulationsschritt
	virtual void vSimulieren() = 0;

	// Getter fuer den Namen - das brauche ich fuer die Funktion vAusgabe in Weg
	virtual string sGetName() const;

	// Einlesefunktion
	virtual void vEinlesen(istream& i);
};

// Ueberladung von <<
ostream& operator<<(ostream& o, const Simulationsobjekt&);

// Ueberladung von >>
istream& operator>>(istream& i, Simulationsobjekt&);
