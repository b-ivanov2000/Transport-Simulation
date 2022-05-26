#include "Kreuzung.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include <random>

Kreuzung::Kreuzung() 
	:Simulationsobjekt()
{
	cout << "Typ des Simulationsobjektes: Kreuzung" << endl;
	cout << endl;
}

Kreuzung::Kreuzung(string sName, double dTankstelle)
	:Simulationsobjekt(sName), p_dTankstelle(dTankstelle)
{
	cout << "Typ des Simulationsobjektes: Kreuzung" << endl;
	cout << endl;
}

Kreuzung::~Kreuzung()
{
}

void Kreuzung::vVerbinde(string sHinWeg, string sRueckWeg, double dWegLaenge,
	shared_ptr<Kreuzung> pStartKreuzung, shared_ptr<Kreuzung> pZielKreuzung, Tempolimit eTempolimit, bool bUeberholverbot)
{
	shared_ptr<Weg> HinWeg = make_shared<Weg>(sHinWeg, dWegLaenge, eTempolimit, bUeberholverbot, pZielKreuzung);
	shared_ptr<Weg> RueckWeg = make_shared<Weg>(sRueckWeg, dWegLaenge, eTempolimit, bUeberholverbot, pStartKreuzung);

	HinWeg->vSetReuckWeg(RueckWeg);
	RueckWeg->vSetReuckWeg(HinWeg);
	pStartKreuzung->p_pWege.push_back(move(HinWeg));
	pZielKreuzung->p_pWege.push_back(move(RueckWeg));


}

void Kreuzung::vTanken(Fahrzeug& aFzg)
{
	if (this != nullptr)
	{
		if (p_dTankstelle > 0.0)
		{
			// Das Volumen wird von der Tankstelle entfernt
			// Immer vollgetankt nach Aufgabestellung
			double dVolumenZuTanken = aFzg.dTanken();
			p_dTankstelle -= dVolumenZuTanken;
			if (p_dTankstelle < 0.0)
			{
				p_dTankstelle = 0.0;
			}
			cout << "Fahrzeug  " << aFzg.sGetName() << " wird mit " << dVolumenZuTanken << " Litern getankt" << endl;
		}
	}
}

void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> pFzg, double dZeit)
{
	if (pFzg != nullptr)
	{
		// das Fahrzeug wird in Streckenende getankt
		
		// der erste Weg von p_pWege nimmt das Fahrzeug parkend an
		(*p_pWege.begin())->vAnnahme(move(pFzg), dZeit);
	}
}

void Kreuzung::vSimulieren()
{
	for (auto& it : p_pWege)
	{
		it->vSimulieren();
	}
}

Weg& Kreuzung::pZufaelligerWeg(Weg& aWeg)
{
	// falls der Weg eine Sachgasse ist, gibt es nur einen Rueckweg
	if (p_pWege.size() == 1)
	{
		return *p_pWege.front();
	}
	else
	{
		shared_ptr<Weg> pWegAuswahl;
		int seed = 0;
		int iListeWegeGroesse = static_cast<int>(p_pWege.size());
		static mt19937 device(seed);
		uniform_int_distribution<int> dist(1, iListeWegeGroesse);
		do {
			// Mit dem Zaehler wird den Weg bestimmt => muss mit iWelcherWeg uebereinstimment
			int iZaehler = 1;
			int iWelcherWeg = dist(device);
			for (auto it = p_pWege.begin(); it != p_pWege.end(); it++)
			{
				if (iZaehler == iWelcherWeg)
				{
					pWegAuswahl = *it;
				}
				iZaehler++;
			}
		} while (*pWegAuswahl == aWeg.pGetRueckweg()); //Rückweg darf nicht gewählt werden
		return *(move(pWegAuswahl));
	}
}

double Kreuzung::dGetTankstelle() const
{
	return p_dTankstelle;
}

void Kreuzung::vAusgeben(ostream& o) const
{
	Simulationsobjekt::vAusgeben(o);
	cout << "Tankinhalt: " << fixed << p_dTankstelle << endl;
}

void Kreuzung::vKopf()
{
	cout << setw(4) << "ID" << setw(6) << "Name" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------";
	cout << endl;
}

void Kreuzung::vEinlesen(istream& in)
{
	Simulationsobjekt::vEinlesen(in);
	in >> p_dTankstelle;
}

int Kreuzung::iGetListeWegeGroesse() const
{
	return static_cast<int>(p_pWege.size());
}
