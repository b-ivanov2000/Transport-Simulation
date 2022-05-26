#pragma once
#include "Simulationsobjekt.h"
#include <list>
#include "Tempolimit.h"
#include <iomanip>
#include "vertagt_liste.h"

class Fahrzeug;
class Kreuzung;

class Weg :
    public Simulationsobjekt
{
protected:
    // Laenge in km
    double p_dLaenge = 0;

    // Fahrzeuge auf dem Weg
    vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeuge;

    // max zulaessige Geschwindigkeit
    Tempolimit p_eTempolimit = Tempolimit::Autobahn;

    // Ueberholverbot
    bool p_bUeberholverbot = true;

    // die virtuelle Schranke fuer das Uberholverbot
    double p_dVirtuelleSchranke = 0;


    // weak_ptr, sodass diese die Zyklen von Kreuzungen und Wegen vermieden werden. Mit share_ptr werden die Objekte gegenseitig aufeinander zeigen
    // Zielkreuzung
    const weak_ptr<Kreuzung> p_pZielkreuzung;
    //Rückweg
    // nicht const da spaeter mit Setter veraendert wird
    weak_ptr<Weg> p_pRueckweg;

public:
    // Defaultkonstruktor
    Weg();

    // Konstruktor
    Weg(string sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::Autobahn, bool bUeberholverbot = true,
        shared_ptr<Kreuzung> pZielKreuzung = nullptr);

    // Destruktor
    virtual ~Weg();

    // Verbot des Copy-Konstruktors
    Weg(const Weg&) = delete;

    // Tempolimit
    double dGetTempolimit() const;

    //Simulationsschritt
    virtual void vSimulieren() override;

    // Ausgabefunktion
    virtual void vAusgeben(ostream& o = cout) const override;

    // Ueberschrift
    static void vKopf();

    // Getter fuer die Laenge
    double dGetLaenge() const;

    // Neues fahrendes Fahrzeug auf dem Weg
    void vAnnahme(unique_ptr<Fahrzeug>);

    // Neues geparktes Fahrzeug auf dem Weg
    void vAnnahme(unique_ptr<Fahrzeug>, double);

    // Ausgabe der Fahrzeuge auf dem Weg
    void vFahrzeugeAusgabe(ostream& o = cout) const;

    // Loeschen eines Objekts aus der Liste mit den Fahrzeugen
    unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug&);

    // Getter fuer die virtuelle Schranke
    double dGetVirtuelleSchranke() const;

    // Setter fuer die virtuelle Schranke
    void vSetVirtuelleSchranke(double dSchranke);

    // Getter fuer die Zielkreuzung
    Kreuzung& pGetZielkreuzung() const;

    // Getter fuer den Rueckweg
    Weg& pGetRueckweg() const;

    // Setter fuer den Rueckweg
    void vSetReuckWeg(shared_ptr<Weg> ReuckWeg);
};

