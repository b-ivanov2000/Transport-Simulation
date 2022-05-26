#pragma once
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"
#include "Kreuzung.h"
#include "Simulation.h"

#include <memory>
#include <vector>
#include <cmath>
#include <string>
#include "Simuclient.h"
#include <random>
#include <fstream>

using namespace std;
// Globaler Uhr
double dGlobaleZeit = 0.0;

void vAufgabe_1()
{
	// statisch erzeugte Elemente:
	Fahrzeug stFahrz1;
	Fahrzeug stFahrz2("Goscho");

	// dynamisch erzeugte elemente:
	Fahrzeug* dynFahrz1 = new Fahrzeug;
	Fahrzeug* dynFahrz2 = new Fahrzeug("Pescho");

	// loeschen von dynamisch erzeugten Objekten
	delete dynFahrz1;
	delete dynFahrz2;

	// unique_ptr
	auto unFahrz1 = make_unique<Fahrzeug>();
	auto unFahrz2 = make_unique<Fahrzeug>("Mincho");
	// das geht nicht:   auto u_fahzr3 = u_fahrz2;

	// shared_ptr
	auto shFahrz1 = make_shared<Fahrzeug>();
	cout << "Anzahl von dublierten shared_ptr: " << shFahrz1.use_count() << endl;
	cout << endl;
	auto shFahrz2 = make_shared<Fahrzeug>("Marta");
	cout << "Anzahl von dubliertern shared_ptr: " << shFahrz2.use_count() << endl;
	cout << endl;
	auto shFahrz3 = shFahrz2;
	cout << "Anzahl von dublierten shared_ptr: " << shFahrz3.use_count() << endl;
	cout << endl;

	// Vektor mit unique_ptr
	vector<unique_ptr<Fahrzeug>> vekunFahrz;
	// Uebertragung des Besitzes von den unique_ptr's
	vekunFahrz.push_back(move(unFahrz1));
	vekunFahrz.push_back(move(unFahrz2));
	// ufahrz1 und ufahrz2 sind jetzt nullptr
	vekunFahrz.clear();
	// hier werden die beiden Elemente von vfahrz geloescht und dementsprechend der Destruktor aufgeruft.

	// Vektor mit shared_ptr
	vector<shared_ptr<Fahrzeug>> vekshFahrz2;
	vekshFahrz2.push_back(move(shFahrz1));
	// jetzt ist s_fahrz1 nullptr
	cout << "Anzahl von dublierten shared_ptr in vfahrz2: " << vekshFahrz2.back().use_count() << endl;
	vekshFahrz2.push_back(shFahrz2);
	// heir aber beinhaltet s_fahrz2 sein Besitzes
	cout << "Anzahl von dublierten shared_ptr in vfahrz2: " << vekshFahrz2.front().use_count() << " bzw. " << vekshFahrz2.back().use_count() << endl;
	cout << endl;

	// ZU NOTIEREN hier in Konsol zeigt es 1 bzw. 3, weil s_fahrz2 verliert sein Content nicht und so gibt es 3 shared_ptrs - s_fahrz2, s_fahrz3 und vs_fahrz.bakc()
	// am Ende der Funktion wird das Content von vs_fahrz2 geloescht
	// die 3 shared_ptrs werden auf einmal vom Compiler geloescht

	Fahrzeug probe1("PKW1", 40);
	Fahrzeug probe2("AUTO3", 30);
	Fahrzeug::vKopf();
	cout << endl;
	cout << probe1;
	cout << endl;
	cout << probe2;
	cout << endl;
	cout << endl;

}

void vAufgabe_1a()
{
	vector<unique_ptr<Fahrzeug>> vekFahrz;
	for (int i = 1; i < 4; i++)
	{
		string sName;
		double dMaxGeschwindigkeit;
		cout << i << ".ter Name: ";
		cin >> sName;
		cout << "Geschwindigkeit des " << i << ".ten Fahrzeugs: ";
		cin >> dMaxGeschwindigkeit;
		cout << endl;
		vekFahrz.push_back(make_unique<Fahrzeug>(sName, dMaxGeschwindigkeit));
	}

	while (dGlobaleZeit <= 2)
	{
		Fahrzeug::vKopf();
		cout << endl;
		for (int i = 0; i < 3; i++)
		{
			vekFahrz[i]->vSimulieren();
			cout << *vekFahrz[i];
			cout << endl;
		}
		dGlobaleZeit += 0.25;
	}
	cout << endl;
}

void vAufgabe_2()
{
	int iAnzahl;
	vector<unique_ptr<Fahrzeug>> vekunFahrz;
	cout << "Anzahl der zu erzeugenden PKWs: ";
	cin >> iAnzahl;
	for (int i = 1; i <= iAnzahl; i++)
	{
		// Name
		string sName;
		cout << "Name des " << i << ".ten PKWs : ";
		cin >> sName;
		// Max Geschwindigkeit
		double dMaxGeschw;
		cout << "Geschwindigkeit des " << i << ".ten PKWs : ";
		cin >> dMaxGeschw;
		// Verbrauch
		double dVerbrauch;
		cout << "Verbrauch des " << i << ".ten PKWs in Liter/100km: ";
		cin >> dVerbrauch;

		string wahl;
		cout << "Wollen Sie den Tankinhalt eingeben? [Y/N] ";
		cin >> wahl;
		if (wahl == "Y")
		{
			double dTankinhalt;
			cout << "Tankinhalt des " << i << ".ten PKWs : ";
			cin >> dTankinhalt;
			cout << endl;
			vekunFahrz.push_back(make_unique<PKW>(sName, dMaxGeschw, dVerbrauch, dTankinhalt));
		}
		else
		{
			cout << endl;
			vekunFahrz.push_back(make_unique<PKW>(sName, dMaxGeschw, dVerbrauch));
		}
	}

	cout << "Anzahl der zu erzeugenden Fahrraeder: ";
	cin >> iAnzahl;
	for (int i = 1; i <= iAnzahl; i++)
	{
		// Name
		string sName;
		cout << "Name des " << i << ".ten Fahrrads : ";
		cin >> sName;
		// Max Geschwindigkeit
		double dMaxGeschw;
		cout << "Geschwindigkeit des " << i << ".ten Fahrrads: ";
		cin >> dMaxGeschw;
		cout << endl;
		vekunFahrz.push_back(make_unique<Fahrrad>(sName, dMaxGeschw));
	}

	double dDauer;
	cout << "Simulationsdauer: ";
	cin >> dDauer;
	// Dauer an der globalen Zeit anpassen
	dDauer += dGlobaleZeit;

	double dZeittakt;
	cout << "Zeittakt: ";
	cin >> dZeittakt;
	// Variable zu ueberpruefen, ob das PKW schon getankt ist
	bool bAreTanked = false;

	while (dGlobaleZeit <= dDauer)
	{
		cout << endl;
		cout << "Globale Zeit: " << dGlobaleZeit << endl;
		Fahrzeug::vKopf();

		if (dGlobaleZeit >= 3 && bAreTanked == false)
		{
			// Wenn es 3 wird, werden die PKWs getankt
			for (auto& it : vekunFahrz)
			{
				it->dTanken();
			}
			bAreTanked = true;

		}
		cout << endl;
		dGlobaleZeit += dZeittakt;

		for (auto& it : vekunFahrz)
		{
			cout << *it;
			it->vSimulieren();
			cout << endl;
		}
	}
	cout << endl;
}

void vAufgabe_3()
{
	auto tt = make_unique<PKW>("Audi TT", 250, 5.9, 50);
	auto yaris = make_unique<PKW>("Toyota Yaris", 160, 4.7, 36);
	
	cout << "Test von Ausgabe" << endl;
	Fahrzeug::vKopf();
	cout << endl;
	cout << *tt << endl;
	cout << *yaris << endl;
	cout << endl;

	cout << "Test von Operator <" << endl;
	dGlobaleZeit = 5;
	tt->vSimulieren();
	yaris->vSimulieren();
	Fahrzeug::vKopf();
	cout << endl;
	cout << *tt << endl;
	cout << *yaris << endl;
	cout << endl;

	cout << "Ist es wahr, dass Audi TT's Gesamtstrecke groesser ist als diese von Toyota Yaris: ";
	cout << ((*yaris < *tt) ? "Wahr" : "Falsch") << endl;
	cout << endl;

	cout << "Test von Operator =" << endl;
	*yaris = *tt;
	Fahrzeug::vKopf();
	cout << endl;
	cout << *tt << endl;
	cout << *yaris << endl;
	cout << endl;
}

void vAufgabe_4()
{
	Weg Landstrasse("Landstrasse", 30, Tempolimit::Landstrasse);
	Weg Autobahn("Autobahn", 20);
	Weg::vKopf();
	cout << Landstrasse << endl;
	cout << Autobahn << endl;
	cout << endl;
}

void vAufgabe_5()
{
	Weg randStrasse("Random", 50, Tempolimit::Innerorts);
	randStrasse.vAnnahme(make_unique<PKW>("BMW", 100, 10, 100));
	randStrasse.vAnnahme(make_unique<PKW>("Audi", 20, 5, 80), 4);
	randStrasse.vAnnahme(make_unique<Fahrrad>("BMX", 20));


	double dDauer = 8;
	double dZeittakt = 0.4;

	while (dGlobaleZeit <= dDauer)
	{
		cout << endl;
		cout << "Globale Zeit: " << dGlobaleZeit << endl;
		Weg::vKopf();
		dGlobaleZeit += dZeittakt;
		randStrasse.vAusgeben();
		cout << endl;
		randStrasse.vSimulieren();
		cout << endl;
	}
}

void vAufgabe_6()
{
	bInitialisiereGrafik(800, 500);
	Weg Goscho("Goscho", 500.0, Tempolimit::Landstrasse);
	Weg Mintscho("Mintscho", 500.0, Tempolimit::Landstrasse);

	int iKoord[] = { 700 , 250 , 100 , 250 };

	bZeichneStrasse(Mintscho.sGetName(), Goscho.sGetName(), Goscho.dGetLaenge(), 2, iKoord);


	// hier benutze ich grossere Tankinhalte, sodass alle Fahrzeuge ans Ende kommen
	Goscho.vAnnahme(make_unique<PKW>("BMW", 100, 5, 900), 4);
	Goscho.vAnnahme(make_unique<Fahrrad>("BMX1", 40));

	Mintscho.vAnnahme(make_unique<PKW>("Audi", 100, 5, 900));
	Mintscho.vAnnahme(make_unique<Fahrrad>("BMX2", 50));

	double dDauer = 8;
	double dZeittakt = 0.3;

	bool bNeuesFzg = false;

	while (dGlobaleZeit <= dDauer)
	{
		cout << endl;
		cout << "Globale Zeit: " << dGlobaleZeit << endl;
		vSetzeZeit(dGlobaleZeit);

		if ((dGlobaleZeit > dDauer / 2) && (bNeuesFzg == false))
		{
			Mintscho.vAnnahme(make_unique<PKW>("VW", 100, 15, 900), (dDauer / 2) + 1);
			bNeuesFzg = true;
		}

		Goscho.vSimulieren();
		Mintscho.vSimulieren();

		cout << Goscho << endl;
		cout << Mintscho << endl;

		cout << endl;
		vSleep(100);
		dGlobaleZeit += dZeittakt;
	}

	vBeendeGrafik();
}

void vAufgabe_6a()
{
	int seed = 0;
	static mt19937 device(seed);
	uniform_int_distribution<int> dist(1, 10);
	vertagt::VListe<int> Liste;

	for (int i = 0; i < 10; i++)
	{
		Liste.push_back(dist(device));
	}
	Liste.vAktualisieren();

	for (auto it = Liste.begin(); it != Liste.end(); it++)
	{
		cout << *it << " ";
	}

	// Erase >5
	for (auto it = Liste.begin(); it != Liste.end(); it++)
	{
		if (*it > 5)
		{
			Liste.erase(it);
		}
	}

	cout << endl;
	// Noch keine Aenderungen
	for (auto it = Liste.begin(); it != Liste.end(); it++)
	{
		cout << *it << " ";
	}

	Liste.vAktualisieren();
	cout << endl;
	// Schon geaendert
	for (auto it = Liste.begin(); it != Liste.end(); it++)
	{
		cout << *it << " ";
	}

	// Random Zahlen hinfuegen
	Liste.push_front(69);
	Liste.push_back(69);

	Liste.vAktualisieren();
	cout << endl;
	for (auto it = Liste.begin(); it != Liste.end(); it++)
	{
		cout << *it << " ";
	}
}

void vAufgabe_7()
{
	bInitialisiereGrafik(1000, 600);

	// Kreuzungen
	shared_ptr<Kreuzung> Kr1 = make_shared<Kreuzung>("Kr1");
	shared_ptr<Kreuzung> Kr2 = make_shared<Kreuzung>("Kr2", 1000);
	shared_ptr<Kreuzung> Kr3 = make_shared<Kreuzung>("Kr3");
	shared_ptr<Kreuzung> Kr4 = make_shared<Kreuzung>("Kr4");

	// Strassen
	Weg W12("W12", 40.0, Tempolimit::Innerorts, true, Kr2);
	Weg W21("W21", 40.0, Tempolimit::Innerorts, true, Kr1);
	int iKoordStrasse1[4] = {680, 40, 680, 300};

	Weg W23a("W23a", 115.0, Tempolimit::Autobahn, false, Kr3); 
	Weg W32a("W32a", 115.0, Tempolimit::Autobahn, false, Kr2);
	int iKoordStrasse2[12] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570};


	Weg W23b("W23b", 40.0, Tempolimit::Innerorts, true, Kr3);
	Weg W32b("W32b", 40.0, Tempolimit::Innerorts, true, Kr2);
	int iKoordStrasse3[4] = {680, 300, 680, 570};

	Weg W24("W24", 55.0, Tempolimit::Innerorts, true, Kr4);
	Weg W42("W42", 55.0, Tempolimit::Innerorts, true, Kr2);
	int iKoordStrasse4[4] = {680, 300, 320, 300};

	Weg W34("W34", 85.0, Tempolimit::Autobahn, false, Kr4);
	Weg W43("W43", 85.0, Tempolimit::Autobahn, false, Kr3);
	int iKoordStrasse5[10] = {680, 570, 500, 570, 350, 510, 320, 420, 320, 300};

	Weg W44a("W44a", 130.0, Tempolimit::Landstrasse, false, Kr4);
	Weg W44b("W44b", 130.0, Tempolimit::Landstrasse, false, Kr4);
	int iKoordStrasse6[14] = {320, 300, 320, 150, 200, 60, 80, 90, 70, 250, 170, 300, 320, 300};

	// Verbindungen
	Kreuzung::vVerbinde("W12", "W21", W12.dGetLaenge(), Kr1, Kr2, Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde("W23b", "W32b", W23b.dGetLaenge(), Kr2, Kr3, Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde("W23a", "W32a", W23a.dGetLaenge(), Kr2, Kr3, Tempolimit::Autobahn, false);
	Kreuzung::vVerbinde("W24", "W42", W24.dGetLaenge(), Kr2, Kr4, Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde("W34", "W43", W34.dGetLaenge(), Kr3, Kr4, Tempolimit::Autobahn, false);
	Kreuzung::vVerbinde("W44a", "W44b", W44a.dGetLaenge(), Kr4, Kr4, Tempolimit::Landstrasse, false);



	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	bZeichneStrasse(W12.sGetName(), W21.sGetName(), W12.dGetLaenge(), 2, iKoordStrasse1);
	bZeichneStrasse(W23a.sGetName(), W32a.sGetName(), W23a.dGetLaenge(), 6, iKoordStrasse2);
	bZeichneStrasse(W23b.sGetName(), W32b.sGetName(), W23b.dGetLaenge(), 2, iKoordStrasse3);
	bZeichneStrasse(W24.sGetName(), W42.sGetName(), W42.dGetLaenge(), 2, iKoordStrasse4);
	bZeichneStrasse(W34.sGetName(), W43.sGetName(), W34.dGetLaenge(), 5, iKoordStrasse5);
	bZeichneStrasse(W44a.sGetName(), W44b.sGetName(), W44b.dGetLaenge(), 7, iKoordStrasse6);

	Kr1->vAnnahme(make_unique<PKW>("Yaris", 150, 15, 200), 1);
	Kr1->vAnnahme(make_unique<PKW>("TT", 90, 15, 85), 2);
	Kr1->vAnnahme(make_unique<PKW>("Golf", 70, 10, 100), 4);
	Kr1->vAnnahme(make_unique<Fahrrad>("BMX", 30), 3);


	double dDauer = 4;
	double dZeittakt = 0.4;

	while (dGlobaleZeit <= dDauer)
	{
		cout << endl;
		cout << "Globale Zeit: " << dGlobaleZeit << endl;
		vSetzeZeit(dGlobaleZeit);
		Kr1->vSimulieren();
		Kr2->vSimulieren();
		Kr3->vSimulieren();
		Kr4->vSimulieren();
		vSleep(500);
		dGlobaleZeit += dZeittakt;
	}

	vBeendeGrafik();
}

void vAufgabe_8()
{
	ifstream infile("VO.dat");
	
	// so wird ein Exception geworfen, falls die Datei falsch eingelesen wird
	infile.exceptions(ios_base::eofbit | ios_base::failbit | !ios_base::badbit);
	
	PKW Porsche;
	Fahrrad Rennrad;
	Kreuzung Kr1;

	try
	{
		infile >> Porsche >> Rennrad >> Kr1;
		Fahrzeug::vKopf();
		cout << Porsche << endl;
		cout << Rennrad << endl;

		cout << endl;
		Kreuzung::vKopf();
		cout << Kr1 << endl;
	}
	catch (runtime_error& e)
	{
		cout << e.what() << endl;
		return;
	}

}

void vAufgabe_9()
{
	ifstream infile("Simu.dat");
	Simulation simu;
	simu.vEinlesen(infile);
	simu.vSimulieren(3, 0.3);
	vBeendeGrafik();
}


void vAufgabe_9a()
{
	ifstream infile("SimuDisplay.dat");
	Simulation simu;
	simu.vEinlesen(infile, true);
	simu.vSimulieren(15, 0.25);
	vBeendeGrafik();
}


int main()
{
	//vAufgabe_1();

	//vAufgabe_1a();

	//vAufgabe_2();

	//vAufgabe_3();

	//vAufgabe_4();

	//vAufgabe_5();

	//vAufgabe_6();

	//vAufgabe_6a();

	//vAufgabe_7();

	//vAufgabe_8();

	//vAufgabe_9();

	vAufgabe_9a();
	return 0;
}