#include "niz.h"


void Niz::kopiraj(const Niz &niz)
{
	if (niz.kapacitet)
	{
		duzina = niz.duzina;
		elementi = new int[kapacitet = niz.kapacitet];
		for (unsigned int i = 0; i < duzina; i++)
			elementi[i] = niz.elementi[i];
	}
	else
	{
		elementi = 0;
		kapacitet = duzina = 0;
	}
}