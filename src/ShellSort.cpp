#include "ShellSort.h"

void ShellSort::sortiraj(Niz * niz)
{
	int size = niz->brElemenata();
	int index = 0, inc, y, k, j, i;
	while (gaps[index] > size) index++;
	
	for (i = index; i < 8; i++) {
		inc = gaps[i];
		for (j = inc; j < size; j++) {
			y = (*niz)[j];
			k = j - inc;
			while (k >= 0 && y < (*niz)[k]) {
				(*niz)[k + inc] = (*niz)[k];
				k -= inc;
				brojZamena++;
			}
			(*niz)[k + inc] = y;
			brojKoraka++;
		}
	}
}
