#pragma once

#include <iostream>
#include <memory>
#include <map>

#include "Kreuzung.h"
#include "Fahrrad.h"
#include "Simulationsobjekt.h"
#include "PKW.h"

using namespace std;
class Simulation
{
private:
	map<string, shared_ptr<Kreuzung>> p_pMapKreuzungen;
public:
	void vEinlesen(istream& in, bool bMitGrafik = false);
	void vSimulieren(double dDauer, double dZeitschritt);
};

