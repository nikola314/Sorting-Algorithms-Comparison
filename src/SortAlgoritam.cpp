#include "SortAlgoritam.h"

bool SortAlgoritam::start(Niz *niz)
{
	if (!niz)
		throw "SortAlgoritam::start - nije zadat niz";

	niz->resetujBrojacPristupa();
	vreme = 0;
	brojKoraka = 0;
	brojZamena = 0;

	LARGE_INTEGER radnaFrekvencija;
	LARGE_INTEGER pocetnoVreme;
	LARGE_INTEGER zavrsnoVreme;

	QueryPerformanceFrequency(&radnaFrekvencija);
	radnaFrekvencija.QuadPart /= 1000;  // od interesa su vremena reda 1 ms i veca
	QueryPerformanceCounter(&pocetnoVreme);

	
	sortiraj(niz);

	QueryPerformanceCounter(&zavrsnoVreme);

	vreme = (zavrsnoVreme.QuadPart - pocetnoVreme.QuadPart) / radnaFrekvencija.QuadPart;
	brojPristupa = niz->brojPristupa();

	return provera(niz);
}

bool SortAlgoritam::provera(Niz *niz)
{
	poredak *por = 0;
	bool uspeh = true;

	switch (dohvatiPoredak())
	{
	case NEOPADAJUCE:
		por = new neopadajuce;
		break;

	case NERASTUCE:
		por = new nerastuce;
		break;

	default:
		throw "SortAlgoritam::provera - nepoznat poredak";
	}

	for (unsigned int i = 0; i < niz->brElemenata() - 1; i++)
		if (!por->p((*niz)[i], (*niz)[i + 1]))
		{
			uspeh = false;
			break;
		}

	delete por;
	return uspeh;
}