#include "Simulation.h"



void Simulation::vEinlesen(istream& in, bool bMitGrafik)
{
	// so wird ein Exception geworfen, falls die Datei falsch eingelesen wird
	in.exceptions(std::ios_base::eofbit | std::ios_base::failbit | std::ios_base::badbit);

	//Zaehler fuer die Zeile
	int iZaehler = 0;

	string sException = "";

	if (bMitGrafik)
	{
		bInitialisiereGrafik(1200, 1200);
	}

	try
	{
	string sSchluesselwort = "";
	in >> sSchluesselwort;
	while (!in.eof())
	{
		iZaehler++;
		if (sSchluesselwort == "KREUZUNG")
		{
			string sName = "";
			in >> sName;
			double dTankstelle = 0.0;
			in >> dTankstelle;

			// falls diese Kreuzung schon vorhanden ist
			if (p_pMapKreuzungen.find(sName) != p_pMapKreuzungen.end())
			{
				sException = "Die Kreuzung " + sName + "ist schon in der Simulation vorhanden";
				throw runtime_error(sException);
			}
			else
			{
				p_pMapKreuzungen[sName] = make_shared<Kreuzung>(sName, dTankstelle);
			}

			// falls mit Grafik
			if (bMitGrafik)
			{
				int iKoordinate1, iKoordinate2;
				in >> iKoordinate1 >> iKoordinate2;
				bZeichneKreuzung(iKoordinate1, iKoordinate2);
			}
		}
		else if (sSchluesselwort == "PKW")
		{
			string sName = "";
			double dGeschwindigkeit = 0.0;
			double dVerbrauch = 0.0;
			double dTankvolumen = 0.0;
			string sStartKreuzung = "";
			double dStartzeitpunkt = 0.0;

			in >> sName;
			in >> dGeschwindigkeit;
			in >> dVerbrauch;
			in >> dTankvolumen;
			in >> sStartKreuzung;
			in >> dStartzeitpunkt;

			// falls die Startkreuzung nicht im Map ist
			if (p_pMapKreuzungen.find(sStartKreuzung) == p_pMapKreuzungen.end())
			{
				sException = "Die Startkreuzung " + sStartKreuzung + " vom PKW " + sName + " ist nich vorhanden";
				throw runtime_error(sException);
			}
			else
			{
				// prueft, ob die Kreuzung nachfolgende Wege hat
				if (p_pMapKreuzungen.find(sStartKreuzung)->second->iGetListeWegeGroesse() > 0)
				{
					unique_ptr<PKW> pPKW = make_unique<PKW>(sName, dGeschwindigkeit, dVerbrauch, dTankvolumen);

					// Die Startkreuzung nimmt den PKW an
					p_pMapKreuzungen[sStartKreuzung]->vAnnahme(move(pPKW), dStartzeitpunkt);
				}
				else
				{
					sException = "Die Startkreuzung " + sStartKreuzung + " hat keine nachfolgenden Wege";
					throw runtime_error(sException);
				}
			}
		}
		else if (sSchluesselwort == "FAHRRAD")
		{
			string sName = "";
			double dGeschwindigkeit = 0.0;
			string sStartKreuzung = "";
			double dStartzeitpunkt = 0.0;

			in >> sName;
			in >> dGeschwindigkeit;
			in >> sStartKreuzung;
			in >> dStartzeitpunkt;

			// falls die Startkreuzung nicht im Map ist
			if (p_pMapKreuzungen.find(sStartKreuzung) == p_pMapKreuzungen.end())
			{
				sException = "Die Startkreuzung " + sStartKreuzung + " vom Fahrrad " + sName + " ist nich vorhanden";
				throw runtime_error(sException);
			}
			else
			{
				// prueft, ob die Kreuzung nachfolgende Wege hat
				if (p_pMapKreuzungen.find(sStartKreuzung)->second->iGetListeWegeGroesse() != 0)
				{
					unique_ptr<Fahrrad> pFahrrad = make_unique<Fahrrad>(sName, dGeschwindigkeit);

					// Die Startkreuzung nimmt das Fahrrad an
					p_pMapKreuzungen[sStartKreuzung]->vAnnahme(move(pFahrrad), dStartzeitpunkt);
				}
				else
				{
					sException = "Die Startkreuzung " + sStartKreuzung + " hat keine nachfolgenden Wege";
					throw runtime_error(sException);
				}
			}
		}
		else if (sSchluesselwort == "STRASSE")
		{
			string sStartKreuzung = "";
			string sZielKreuzung = "";
			string sHinWeg = "";
			string sRueckWeg = "";
			double dWegLaenge = 0.0;

			int iTempolimit = 0;
			Tempolimit eLimit;

			// ein int wird fuer die Ueberpruefung benoetigt
			int iUeberholverbot = 0;
			bool bUeberholverbot = 0;

			int iAnzahlPaare = 0;

			in >> sStartKreuzung;
			in >> sZielKreuzung;
			in >> sHinWeg;
			in >> sRueckWeg;
			in >> dWegLaenge;
			in >> iTempolimit;
			in >> iUeberholverbot;

			// Prueft, ob die Startkreuzung schon existiert
			if (p_pMapKreuzungen.find(sStartKreuzung) == p_pMapKreuzungen.end())
			{
				sException = "Die Startkreuzung " + sStartKreuzung + " ist nich vorhanden";
				throw runtime_error(sException);
			}

			// Prueft, ob die Zielkreuzung schon existiert
			if (p_pMapKreuzungen.find(sZielKreuzung) == p_pMapKreuzungen.end())
			{
				sException = "Die Zielkreuzung " + sZielKreuzung + " ist nich vorhanden";
				throw runtime_error(sException);
			}

			// Tempolimit
			switch (iTempolimit)
			{
			case 1:
				eLimit = Tempolimit::Innerorts;
				break;
			case 2:
				eLimit = Tempolimit::Landstrasse;
				break;
			case 3:
				eLimit = Tempolimit::Autobahn;
				break;
			default:
				throw runtime_error("Out of range Tempolimit: 1, 2 oder 3");
				break;
			}

			// Ueberholverbot
			switch (iUeberholverbot)
			{
			case 0:
				bUeberholverbot = false;
				break;
			case 1:
				bUeberholverbot = true;
				break;
			default:
				throw runtime_error("Out of range Tempolimit: 0 oder 1");
			}

			// Verbindet dien Wege
			Kreuzung::vVerbinde(sHinWeg, sRueckWeg, dWegLaenge, p_pMapKreuzungen[sStartKreuzung],
				p_pMapKreuzungen[sZielKreuzung], eLimit, bUeberholverbot);

			if (bMitGrafik)
			{
				in >> iAnzahlPaare;
				int iKoordinaten[70];
				int iKoord = 0;
				for (int i = 0; i < 2 * iAnzahlPaare; i++)
				{
					in >> iKoord;
					iKoordinaten[i] = iKoord;
				}
				bZeichneStrasse(sHinWeg, sRueckWeg, dWegLaenge, iAnzahlPaare, iKoordinaten);
			}
		}
		// falls der Schluesselwort nicht gefunden wird
		else
		{
			throw runtime_error("Schluesselwort wird nicht gefunden!");
		}
		in >> sSchluesselwort;
	}
	}
	catch (runtime_error& e)
	{
		cout << e.what() << endl;
		cout << "Fehler in der Zeile: " << iZaehler << endl;
	}
}

void Simulation::vSimulieren(double dDauer, double dZeitschritt)
{
	while (dGlobaleZeit <= dDauer)
	{
		cout << "Globale Zeit: " << dGlobaleZeit << endl;
		vSetzeZeit(dGlobaleZeit);
		for (auto it : p_pMapKreuzungen)
		{
			(it).second->vSimulieren();
		}
		vSleep(100);
		dGlobaleZeit += dZeitschritt;
	}
}