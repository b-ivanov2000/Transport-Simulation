#pragma once
#include "Simulationsobjekt.h"
#include "Tempolimit.h"

#include <list>
#include <memory>
#include <string>

class Weg;
class Fahrzeug;

class Kreuzung :
    public Simulationsobjekt
{
private:
    // von der Kreuzung wegfuehrenden Wege
    list<shared_ptr<Weg>> p_pWege;

    // Tankvolumen der Kreuzung
    double p_dTankstelle = 0;

public:
    // Default-Konstruktor
    Kreuzung();
    // Konstruktor
    Kreuzung(string sName, double dTankstelle = 0);
    // Destruktor
    virtual ~Kreuzung();


    // Verbindet 2 Kreuzungen mit 2 Wegen - Hin und Zurueck
    // statisch, da man den this-Zeiger nicht in einen Smartpointer umwandeln kann
    static void vVerbinde(string sHinWeg, string sRueckWeg, double dWegLaenge,
        shared_ptr<Kreuzung> pStartKreuzung, shared_ptr<Kreuzung> pZielkreuzung, Tempolimit eTempolimit, bool bUeberholverbot = true);

    // Tanken
    void vTanken(Fahrzeug& aFzg);

    // Kreuzung nimmt ein Fahrzeug und parkt es auf die abgehende Strasse und tankt es
    void vAnnahme(unique_ptr<Fahrzeug> pFzg, double dZeit);

    // Simulation von den abgehenden Wegen von der Kreuzung
    void vSimulieren();

    // Waehlt einen zufaelligen Weg
    Weg& pZufaelligerWeg(Weg& aWeg);

    // Getter fuer das Tankstellevolumen
    double dGetTankstelle() const;

    // Kreuzung ausgeben - sodass vAusgeben rein virtuelle Methode ist
    virtual void vAusgeben(ostream& o) const override;

    static void vKopf();

    // Einlesefunktion
    void vEinlesen(istream& in) override;

    // Getter fuer die Groesse der Liste mit den Wegen
    int iGetListeWegeGroesse() const;
};

