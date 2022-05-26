#pragma once
#include "Fahrzeug.h"

class PKW :
    public Fahrzeug
{
private:
    // Verbrauch in Liter/100km
    double p_dVerbrauch = 0;
    // In Liter
    double p_dTankvolumen = 0;
    // In Liter
    double p_dTankinhalt = 0;
public:
    // Konstruktor
    PKW(string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen = 55);

    // Default-Konstruktor
    PKW();

    // Destruktor
    virtual ~PKW();

    double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;

    void vAusgeben(ostream& o) const override;
    void vSimulieren() override;
    // wenn wir PKW als Argument benutzen kann die Funktion nicht vererbt werden, sondern ueberladen
    void operator=(const PKW& pkw);

    // Gibt die Geschwindigkeit zurueck
    double dGeschwindigkeit() const override;

    // Zeichnung
    void vZeichnen(const Weg&) const override;

    // ob ueberholbar ist
    bool bUberholbar() const override;

    // Einlesefunktion
    void vEinlesen(istream& in) override;
};

