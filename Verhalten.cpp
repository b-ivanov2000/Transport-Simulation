#include "Verhalten.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"

Verhalten::Verhalten(Weg& rWeg)
	: p_rWeg(rWeg)
{
}

Verhalten::~Verhalten()
{
}

double Verhalten::dGetGeschwindigkeitslimit()
{
	return p_rWeg.dGetTempolimit();
}

