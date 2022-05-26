#pragma once
#include "Fahrausnahme.h"
class Losfahren :
    public Fahrausnahme
{
public:
    // Konstruktor
    Losfahren(Fahrzeug& aFzg, Weg& aWeg);

    // Destruktor
    virtual ~Losfahren();

    void vBearbeiten();
};

