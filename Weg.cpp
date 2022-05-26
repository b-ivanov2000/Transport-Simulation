#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"

Weg::Weg()
	:Simulationsobjekt()
{
	cout << "Typ des Simulationsobjektes: Weg" << endl;
	cout << endl;
}

Weg::~Weg()
{
}

Weg::Weg(string sName, double dLaenge, Tempolimit eTempolimit, bool bUeberholverbot, shared_ptr<Kreuzung> pZielKreuzung)
	:Simulationsobjekt(sName), p_dLaenge(dLaenge), p_eTempolimit(eTempolimit), p_bUeberholverbot(bUeberholverbot), p_pZielkreuzung(pZielKreuzung)
{
	cout << "Typ des Simulationsobjektes: Weg" << endl;
	cout << endl;
}

double Weg::dGetTempolimit() const
{
	return (double)(p_eTempolimit);
}

void Weg::vSimulieren()
{
	p_pFahrzeuge.vAktualisieren();
	// Setze die Schranke
	p_dVirtuelleSchranke = p_dLaenge;
	for (auto& it : p_pFahrzeuge)
	{
		try
		{
			it->vSimulieren();
			if (p_bUeberholverbot == true)
			{
				// ob der Tankinhalt > 0 ist
				if (it->bUberholbar() == false)
				{

					// ob Fahrzeug fahrend ist - d.h. das Fahrzeug hat Abschnittstrecke >  0 , da parkende Fahrzeuge sind am Start
					if (it->dGetAbschnittstrecke() > 1e-6)
					{
						vSetVirtuelleSchranke(it->dGetAbschnittstrecke());
					}
				}
			}
			it->vZeichnen(*this);
		}
		catch (Fahrausnahme& aFahrausnahme)
		{
			aFahrausnahme.vBearbeiten();
		}
	}
	p_pFahrzeuge.vAktualisieren();
}

void Weg::vAusgeben(ostream& o) const
{
	Simulationsobjekt::vAusgeben(o);
	o << ": " << setw(9) << p_dLaenge << " (";
	for (auto& it : p_pFahrzeuge) { o << it->sGetName() << " "; }
	o << ")";
}

void Weg::vKopf()
{
	cout << "ID |" << setw(5) << "Name" << setw(15) << "| Laenge" << setw(14) << "| Fahrzeuge" << endl;
	cout << "-----------------------------------------------------------------" << endl;
}

double Weg::dGetLaenge() const
{
	return p_dLaenge;
}

// fahrend => hinten hinzufuegen
void Weg::vAnnahme(unique_ptr<Fahrzeug> pFzg)
{
	if (pFzg != nullptr)
	{
		// Fahrzeug wird auf dem neuen Weg gebracht
		pFzg->vNeueStrecke(*this);

		// Liste mit den Fahrzeugen aktualisieren
		p_pFahrzeuge.push_back(move(pFzg));
	}
}


// gepartk => am Vorne hinzufuegen
void Weg::vAnnahme(unique_ptr<Fahrzeug> pFzg, double dStartzeitpunkt)
{
	if (pFzg != nullptr)
	{
		pFzg->vNeueStrecke(*this, dStartzeitpunkt);
		p_pFahrzeuge.push_front((move(pFzg)));
	}
}

unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& aFzg)
{
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		// Zeiger auf einen Zeiger da urspruenglich ist it ein Zeiger, sodass er einmal dereferenziert wird, um das Fahrzeugobjekt zu bekommen und nocheinmal, um in Simulationsobjekt == als Zeiger zu benutzen
		if ((*it != nullptr) && **it == aFzg)
		{
			unique_ptr<Fahrzeug> pLokaleVariable = move(*it);
			p_pFahrzeuge.erase(it);
			return pLokaleVariable;
		}
	}
	cout << "Bitte geben sie ein gueltiges Fahrzeug ein" << endl;
	return nullptr;
}

double Weg::dGetVirtuelleSchranke() const
{
	if (p_bUeberholverbot == true)
	{
		return p_dVirtuelleSchranke;
	}
	else
	{
		return p_dLaenge;
	}
}

void Weg::vSetVirtuelleSchranke(double dSchranke)
{
	p_dVirtuelleSchranke = dSchranke;
}

Kreuzung& Weg::pGetZielkreuzung() const
{
	return *(p_pZielkreuzung.lock());
}

Weg& Weg::pGetRueckweg() const
{
	return *(p_pRueckweg.lock());
}

void Weg::vSetReuckWeg(shared_ptr<Weg> ReuckWeg)
{
	p_pRueckweg = ReuckWeg;
}