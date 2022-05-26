#pragma once
#include <limits>
using namespace std;

enum class Tempolimit
{
	Innerorts = 50,
	Landstrasse = 100,
	Autobahn = numeric_limits<int>::max()
};