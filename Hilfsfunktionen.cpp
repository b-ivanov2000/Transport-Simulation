#include "Hilfsfunktionen.h"
bool bDoublesGroesser(double a, double b, double epsilon)
{
    return (a - b) >= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

bool bDoublesKleiner(double a, double b, double epsilon)
{
    return (b - a) >= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}
