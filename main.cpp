#pragma once
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"

#include <memory>
#include <vector>
#include <cmath>
#include <string>
#include <list>
using namespace std;
// Globaler Uhr
double dGlobaleZeit = 0.0;

void vAufgabe_AB1() {

	int l = 0; // Laufindex für gezielte AUsgabe
	vector<int> ausgabe{ 15 };
	double dTakt = 0.3;

	std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
	vecFahrzeuge.push_back(make_unique <PKW>("Audi", 229, 9.6));
	vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 24.7));
	for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += dTakt)
	{
		auto itL = find(ausgabe.begin(), ausgabe.end(), l);
		if (itL != ausgabe.end()) {
			std::cout << std::endl << l << " Globalezeit = " << dGlobaleZeit << std::endl;
			Fahrzeug::vKopf();
			cout << endl;
		}

		for (int i = 0; i < vecFahrzeuge.size(); i++)
		{
			vecFahrzeuge[i]->vSimulieren();
			if (fabs(dGlobaleZeit - 3.0) < dTakt / 2)
			{
				vecFahrzeuge[i]->dTanken();
			}
			if (itL != ausgabe.end()) {
				std::cout << *vecFahrzeuge[i] << endl;
			}
		}
		l++;
	}
	char c;
	std::cin >> c;
}

void vAufgabe_Probe() {
	Fahrzeug* pF1 = new PKW("Audi", 150, 8);
	dGlobaleZeit = 0.0;
	Fahrzeug::vKopf();
	dGlobaleZeit = 3.0;
	cout << endl << "Globalezeit = " << dGlobaleZeit << endl;
	pF1->vSimulieren();
	std::cout << *pF1 << endl;
	delete pF1;
	char c;
	std::cin >> c;
}

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
		cout << endl;
		cout << "Globale Zeit: " << dGlobaleZeit << endl;
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

		if ((dGlobaleZeit - 3.0 > 0.0001) && bAreTanked == false)
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

int main()
{
	//vAufgabe_1();
	//vAufgabe_1a();
	//vAufgabe_2();

	//vAufgabe_3();
	//vAufgabe_Probe();
	//vAufgabe_AB1();
	return 0;
}