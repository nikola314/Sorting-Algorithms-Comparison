#ifndef NIZ_H__
#define NIZ_H__

#include <iostream>
using namespace std;

class Niz
{
protected:
	int               *elementi;
	unsigned int      kapacitet;
	unsigned int      duzina;

	unsigned int      brPristupa;

	

	void kopiraj(const Niz &niz);
	void brisi()
	{
		delete[]elementi;
		kapacitet = duzina = 0;
		resetujBrojacPristupa();
	}

public:
	explicit Niz(unsigned int kap = 100)
	{
		if (kap == 0)
			throw "Niz::Niz - nulti kapacitet niza";

		elementi = new int[kapacitet = kap];
		duzina = 0;
		resetujBrojacPristupa();
	}

	Niz(const Niz &niz)
	{
		kopiraj(niz);
	}

	~Niz()
	{
		brisi();
	}

	Niz & operator=(const Niz &niz)
	{
		if (this != &niz)
		{
			brisi(); kopiraj(niz);
		}
		return *this;
	}

	void dodaj(int broj)
	{
		if (duzina >= kapacitet)
			throw "Niz::dodaj - prekoracenje kapaciteta";
		elementi[duzina++] = broj;
	}

	int &operator[](const unsigned int index)
	{
		if (index >= duzina)
			throw "Niz::op[] - greska u indeksu";

		brPristupa++;
		return elementi[index];
	}

	void resetujBrojacPristupa()
	{
		brPristupa = 0;
	}

	unsigned int brojPristupa() const
	{
		return brPristupa;
	}

	unsigned int brElemenata() const
	{
		return duzina;
	}

	friend ostream &operator<<(ostream &os, const Niz &niz)
	{
		for (unsigned int i = 0; i < niz.brElemenata(); i++)
			os << niz.elementi[i] << ' ';

		return os;
	}

};

#endif