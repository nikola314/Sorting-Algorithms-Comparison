#include <windows.h>
#include "niz.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;


#include "HeapSort.h"
#include "BitonicSort.h"
#include "ShellSort.h"

struct params
{
	vector<string> imena_fajlova;
	vector<int> id_algoritama;
	vector<SortAlgoritam *> algoritmi;
	bool info;
	bool nepoznat;
	string opisNepoznatogParametra;
	string imeIzlaznogFajla;


	params()
	{
		info = false;
		nepoznat = false;
	}

	~params()
	{
	}

	void dodajFajl(char *fajl)
	{
		imena_fajlova.push_back(string(fajl));
	}

	void dodajID(int id)
	{
		id_algoritama.push_back(id);
	}

	void dodajAlgoritam(SortAlgoritam *alg)
	{
		algoritmi.push_back(alg);
	}
};

enum tipParametra
{
	ULAZNI_FAJL,
	IZLAZNI_FAJL,
	ID_ALGORITMA,
	INFO,
	NEPOZNAT
};

tipParametra dohvatiTipParametra(char *s)
{
	if (s == NULL)
		return NEPOZNAT;

	tipParametra param = NEPOZNAT;

	switch (s[0])
	{
	case '-':
		switch (s[1])
		{
		case 'u':
			param = ULAZNI_FAJL;
			break;

		case 'i':
			param = IZLAZNI_FAJL;
			break;

		case 'a':
			param = ID_ALGORITMA;
			break;
		}
		break;

	case '/':
		switch (s[1])
		{
		case '?':
			param = INFO;
			break;
		}
		break;
	}

	return param;
}

void procitajParametre(params &par, int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		tipParametra tip = dohvatiTipParametra(argv[i]);
		switch (tip)
		{
		case INFO:
			par.info = true;
			break;

		case ID_ALGORITMA:
			par.dodajID(MAKE_CODE(argv[i][3], argv[i][4], argv[i][5], argv[i][6]));
			break;

		case ULAZNI_FAJL:
			par.dodajFajl(&argv[i][3]);
			break;

		case IZLAZNI_FAJL:
			par.imeIzlaznogFajla = &argv[i][3];
			break;

		case NEPOZNAT:
		default:
			par.opisNepoznatogParametra = argv[i][0];
			par.opisNepoznatogParametra += argv[i][1];
			par.nepoznat = true;
			return;
		}
	}
}


Niz *citajNiz(const string &ime_datoteke)
{
	ifstream datoteka;
	datoteka.open(ime_datoteke.data());

	if (!datoteka.is_open())
		return 0;

	int duzina;
	datoteka >> duzina;
	if (duzina <= 0)
		return 0;

	Niz *n = new Niz(duzina);
	for (int i = 0; i < duzina; i++)
	{
		int br;
		datoteka >> br;
		n->dodaj(br);
	}

	datoteka.close();

	return n;
}


void obrada(SortAlgoritam *algoritam, Niz *niz, ostream &os)
{
	os << "=====================================" << endl;
	os << "Sortiranje metodom: *** " << algoritam->nazivAlgoritma() << " *** ";
	if (!algoritam->start(niz))
	{
		os << " nije uspelo!!" << endl << endl;
	}
	else
	{
		os << endl;
		os << "Duzina niza: " << niz->brElemenata() << endl;
		os << "Vreme: " << algoritam->dohvatiVreme() << " [ms]" << endl;
		os << "Broj pristupa: " << algoritam->dohvatiBrojPristupa() << endl;
		os << "Broj koraka: " << algoritam->dohvatiBrojKoraka() << endl;
		os << "Broj zamena: " << algoritam->dohvatiBrojZamena() << endl;
	}
}

void main(int argc, char *argv[])
{
	//---- ovde treba dodati jos metoda za uredjivanje nizova
	ShellSort ss;
	HeapSort hs;
	BitonicSort bs;
	SortAlgoritam *nizAlgoritama[] = { &hs,&bs,&ss };
	unsigned int brojAlgoritama = sizeof(nizAlgoritama) / sizeof(SortAlgoritam *);


	params mainParams;
	procitajParametre(mainParams, argc, argv);

	if (mainParams.nepoznat)
	{
		cout << "Nepoznat parametar " << mainParams.opisNepoznatogParametra << endl;
		return;
	}

	if (mainParams.info)
	{
		cout << "Upotreba: " << endl;
		cout << argv[0] << " " << " {-<par>=<vr>} {/<opcija>} " << endl;
		cout << "par: " << endl;
		cout << "u: fajl sa podacima (vr je putanja fajla, podrazumevano pravi se slucajan niz)" << endl;
		cout << "i: fajl za rezultate (vr je putanja fajla, podrazumevano standardni izlaz)" << endl;
		cout << "a: aktiviranje algoritma (vr je kod algoritma, podrazumevano svi>" << endl;
		cout << "Dostupni su sledeci algoritmi (akronimi su u zagradama): " << endl;
		for (unsigned int i = 0; i < brojAlgoritama; i++)
			cout << '\t' << nizAlgoritama[i]->nazivAlgoritma() << " (" << nizAlgoritama[i]->akronimAlgoritma() << ")" << endl;
		cout << endl;
		cout << "opcija: " << endl;
		cout << "? : ispisuje ovaj tekst" << endl << endl;

		cout << "Primer:" << endl;
		cout << argv[0] << " -u=neur_10000.txt -a=SESO -a=HESO -i=izlaz.txt" << endl;
		return;
	}


	if (mainParams.id_algoritama.size() == 0)
	{
		for (unsigned int j = 0; j < brojAlgoritama; j++)
			mainParams.dodajAlgoritam(nizAlgoritama[j]);
	}
	else
		for (unsigned int i = 0; i < mainParams.id_algoritama.size(); i++)
		{
			unsigned int j = 0;
			for (; j < brojAlgoritama; j++)
				if (mainParams.id_algoritama[i] == nizAlgoritama[j]->kodAlgoritma())
				{
					mainParams.dodajAlgoritam(nizAlgoritama[j]);
					break;
				}

			if (j == brojAlgoritama)
			{
				char s[4];
				SortAlgoritam::kodUString(mainParams.id_algoritama[i], s);
				cout << "Nepoznat algoritam: " << s << endl;
			}
		}


	Niz *n = 0;
	int duzinaNiza;

	if (mainParams.imena_fajlova.size() == 0)
	{
		cout << "Unesite duzinu niza (0 za prekid): ";
		cin >> duzinaNiza;
		if (duzinaNiza <= 0)
			return;

		n = new Niz(duzinaNiza);
		for (int i = 0; i < duzinaNiza; i++)
			n->dodaj(rand());

	}

	ostream *os = 0;
	ofstream ofs;
	if (mainParams.imeIzlaznogFajla.length() > 0)
	{
		ofs.open(mainParams.imeIzlaznogFajla.data());
		if (ofs.is_open())
			os = &ofs;
		else
		{
			cout << "Greska prilikom otvaranja izlaznog fajla." << endl;
		}
	}

	if (os == 0)
		os = &cout;

	try
	{
		for (unsigned int i = 0; i < mainParams.algoritmi.size(); i++)
		{
			if (n)
			{
				try
				{
					obrada(mainParams.algoritmi[i], n, *os);
				}
				catch (char *s)
				{
					*os << s << endl;
				}
			}
			else
			{
				for (unsigned int j = 0; j < mainParams.imena_fajlova.size(); j++)
				{
					*os << mainParams.imena_fajlova[j];
					Niz *niz = citajNiz(mainParams.imena_fajlova[j]);
					if (niz == 0)
					{
						*os << " ... greska prilikom citanja fajla " << endl;
						continue;
					}

					*os << endl;
					try
					{
						obrada(mainParams.algoritmi[i], niz, *os);
					}
					catch (char *s)
					{
						*os << s << endl;
					}

					delete niz;
				}
			}
		}
	}
	catch (...)
	{
		cout << endl << "Neidentifikovan izuzetak" << endl;
	}


	if (ofs.is_open())
		ofs.close();

	delete n;
}