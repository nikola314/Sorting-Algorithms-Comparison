#include "HeapSort.h"

void HeapSort::makeTheHeap(Niz * niz)
{
	int size = niz->brElemenata();
	int i;
	//making the heap
	int head = 0;
	int ls, ds, bigger;
	int inc = 1;
	i = size / 2 - 1;
	while (i >= head) {
		//might not have right child (no sufficient comparations)	
		ls = (*niz)[2 * i + 1];
		ds = (2 * i + 2) >= size ? -1 : (*niz)[2 * i + 2];
		bigger = ls > ds ? ls : ds;
		if ((*niz)[i] < bigger) {
			if (ls == bigger) {
				//(*niz)[2 * i + 1] = (*niz)[i];
				//(*niz)[i] = bigger;
				zameni(niz, 2 * i + 1, i);
			}
			else {
				//(*niz)[2 * i + 2] = (*niz)[i];
				//(*niz)[i] = bigger;
				zameni(niz, 2 * i + 2, i);
			}
		}
		//all other nodes
		for (i = size / 2 - 2; i >= head; i--) {
			brojKoraka++;
			ls = (*niz)[2 * i + 1];
			ds = (*niz)[2 * i + 2];
			bigger = ls > ds ? ls : ds;
			if ((*niz)[i] < bigger) {
				if (ls == bigger) {
					//(*niz)[2 * i + 1] = (*niz)[i];
					//(*niz)[i] = bigger;
					zameni(niz, 2 * i + 1, i);
				}
				else {
					//(*niz)[2 * i + 2] = (*niz)[i];
					//(*niz)[i] = bigger;
					zameni(niz, 2 * i + 2, i);
				}
			}
		}
		head = inc;
		inc = inc << 1;
		i = size / 2 - 1;
	}
}


void HeapSort::updateTree(Niz* niz, int nSize) {
	int bigger, ls, ds;
	int i = 0;
	while (i < nSize / 2) {
		brojKoraka++;
		ls = (*niz)[2 * i + 1];
		ds = (*niz)[2 * i + 2];
		bigger = ls > ds ? ls : ds;
		if ((*niz)[i] < bigger) {
			if (ls == bigger) {
				zameni(niz, 2 * i + 1, i);
				//(*niz)[i] = bigger;
				i = i * 2 + 1;
			}
			else {
				zameni(niz, 2 * i + 2, i);
				//(*niz)[i] = bigger;
				i = i * 2 + 2;
			}
		}
		else break;
	}
	if (nSize == 0) {
		if ((*niz)[1] < (*niz)[0])
			zameni(niz, 1, 0);
	}
}

void HeapSort::sortiraj(Niz * niz)
{
	int size = niz->brElemenata();
	int ls, ds, bigger;
	int i;

	makeTheHeap(niz);

	//sorting the array:
	int nSize = size-1;
	while (nSize) {
		zameni(niz, nSize--, 0);
		updateTree(niz, nSize);
		}
}

int HeapSort::selektuj(Niz *niz, unsigned int k)
{
	int size = niz->brElemenata();
	int cnt = 0;

	makeTheHeap(niz);

	int nSize = size - 1;
	while (nSize) {
		if (++cnt == k) return (*niz)[0];
		zameni(niz, nSize--, 0);
		updateTree(niz, nSize);
	}
}
