#ifndef SORT_ALGORITAM_H__
#define SORT_ALGORITAM_H__

#include "niz.h"

#include <windows.h>

#define MAKE_CODE(a,b,c,d) ( (a << 24) | (b << 16) | (c << 8) | d )
#define UNMAKE_CODE(code, str) ( str[0] = (code >> 24) & 0xFF,  \
                                 str[1] = (code >> 16) & 0xFF,  \
                                 str[2] = (code >> 8) & 0xFF,  \
                                 str[3] = (code ) & 0xFF  \
                               )

class SortAlgoritam
{
	class poredak
	{
	public:
		virtual bool p(int a, int b) = 0;
	};
	class neopadajuce : public poredak
	{
	public:
		virtual bool p(int a, int b)
		{
			return a <= b;
		}
	};
	class nerastuce : public poredak
	{
	public:
		virtual bool p(int a, int b)
		{
			return a >= b;
		}
	};

	bool provera(Niz *niz);
	
protected:
	LONGLONG          vreme;
	unsigned int      duzinaNiza;
	unsigned int      brojPristupa;
	unsigned int      brojKoraka;
	unsigned int      brojZamena;

	SortAlgoritam()
	{
		duzinaNiza = 0;
		brojKoraka = 0;
		brojZamena = 0;
		brojPristupa = 0;
		vreme = 0;
	}

	virtual void sortiraj(Niz *niz) = 0;
	void zameni(Niz *niz, unsigned int i, unsigned int j)
	{
		int t = (*niz)[i];

		(*niz)[i] = (*niz)[j];
		(*niz)[j] = t;

		brojZamena++;
	}

	enum Poredak { NEOPADAJUCE, NERASTUCE };

public:

	virtual ~SortAlgoritam() { }

	bool start(Niz *niz);

	virtual Poredak dohvatiPoredak() const = 0;
	virtual const char *nazivAlgoritma() const = 0;
	virtual const char *akronimAlgoritma() const = 0; // akronim mora biti tacno duzine 4 znaka

	virtual const int kodAlgoritma() const
	{
		const char *s = akronimAlgoritma();
		return int(MAKE_CODE(s[0], s[1], s[2], s[3]));
	}

	static void kodUString(const int kod, char str[4])
	{
		UNMAKE_CODE(kod, str);
	}

	LONGLONG dohvatiVreme() const
	{
		return vreme;
	}

	unsigned int dohvatiDuzinuNiza() const
	{
		return duzinaNiza;
	}

	unsigned int dohvatiBrojPristupa() const
	{
		return brojPristupa;
	}

	unsigned int dohvatiBrojKoraka() const
	{
		return brojKoraka;
	}

	unsigned int dohvatiBrojZamena() const
	{
		return brojZamena;
	}
};

#endif