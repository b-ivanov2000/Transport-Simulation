#pragma once
#include "Fahrausnahme.h"
#include "Kreuzung.h"
class Streckenende :
    public Fahrausnahme
{
public:
    // Konstruktor
    Streckenende(Fahrzeug& aFzg, Weg& aWeg);

    // Destruktor
    virtual ~Streckenende();

    void vBearbeiten();
};

