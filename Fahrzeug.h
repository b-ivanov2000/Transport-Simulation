#pragma once
#include "Simulationsobjekt.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "SimuClient.h"
#include "Weg.h"

using namespace std;

class Weg;
class Verhalten;

class Fahrzeug : public Simulationsobjekt
{

protected:
	double p_dMaxGeschwindigkeit = 0;
	double p_dGesamtStrecke = 0;
	double p_dGesamtZeit = 0;

	// unique_ptr da pro Fahrzeug nur 1 Verhalten moeglich
	unique_ptr<Verhalten> p_pVerhalten = nullptr;

	// die auf dem aktuellen Weg zurückgelegte Strecke
	double p_dAbschnittStrecke = 0;

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
	virtual void vAusgeben(ostream& o) const override;

	// Ueberschrift
	static void vKopf();

	// Simulationsschritt simulieren
	virtual void vSimulieren() override;

	// Tanke
	virtual double dTanken(double dMenge = numeric_limits<double>::infinity());

	// Geschwindigkeit
	virtual double dGeschwindigkeit() const;

	bool operator<(const Fahrzeug& fahrz) const;

	// Verbot von Copy-Konstruktor
	Fahrzeug(const Fahrzeug&) = delete;

	// Zuweisungsoperator =
	void operator=(const Fahrzeug& fahze);

	// Aktualisieren des Wegs fuer fahrende Fahrzeuge
	void vNeueStrecke(Weg& weg);

	// Aktualisieren des Wegs fuer geparkte Fahrzeuge
	void vNeueStrecke(Weg& weg, double dStartzeitpunkt);

	// Getter fuer die Abschnittstrecke
	double dGetAbschnittstrecke() const;

	// Zeichen des Fahrzeugs
	virtual void vZeichnen(const Weg&)const;

	// Fahrzeug zu ueberholbar ist
	virtual bool bUberholbar() const;

	// Einlesefunktion
	virtual void vEinlesen(istream& it) override;
};
