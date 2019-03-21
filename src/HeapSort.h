#ifndef HEAP_SORT_H__
#define HEAP_SORT_H__
#include "sortalgoritam.h"
class HeapSort :
	public SortAlgoritam
{
	void makeTheHeap(Niz* niz);
	void updateTree(Niz * niz, int nSize);
public:
	void sortiraj(Niz *niz);
	const char *nazivAlgoritma() const
	{
		return "Heap Sort";
	}

	const char *akronimAlgoritma() const
	{
		return "HESO";
	}

	int selektuj(Niz*, unsigned int);

	Poredak dohvatiPoredak() const
	{
		return SortAlgoritam::NEOPADAJUCE;
	}
};
#endif

