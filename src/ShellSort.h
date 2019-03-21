#ifndef SHELL_SORT_H__
#define SHELL_SORT_H__
#include "sortalgoritam.h"
class ShellSort :
	public SortAlgoritam
{
	int gaps[8] = { 701,301,132,57,23,10,4,1 };
public:
	void sortiraj(Niz *niz);
	const char *nazivAlgoritma() const
	{
		return "Shell Sort";
	}

	const char *akronimAlgoritma() const
	{
		return "SHSO";
	}

	Poredak dohvatiPoredak() const
	{
		return SortAlgoritam::NEOPADAJUCE;
	}
};
#endif
