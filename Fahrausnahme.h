#pragma once
#include <exception>

#include "Fahrzeug.h"
#include "Weg.h"

using namespace std;

class Fahrausnahme :
    public exception
{
protected:
    Fahrzeug& p_aFzg;
    Weg& p_aWeg;

public:
    // Konstruktor
    Fahrausnahme(Fahrzeug& aFzg, Weg& aWeg);

    //Destruktor
    virtual ~Fahrausnahme();

    virtual void vBearbeiten() = 0;
};

