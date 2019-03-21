#ifndef BITONIC_SORT_H__
#define BITONIC_SORT_H__
#include "sortalgoritam.h"
class BitonicSort :
	public SortAlgoritam
{
public:
	void sortiraj(Niz *niz);
	const char *nazivAlgoritma() const
	{
		return "Bitonic Sort";
	}

	const char *akronimAlgoritma() const
	{
		return "BTSO"; 
	}

	Poredak dohvatiPoredak() const
	{
		return SortAlgoritam::NEOPADAJUCE;
	}
};

#endif