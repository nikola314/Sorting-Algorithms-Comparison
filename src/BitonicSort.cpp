#include "BitonicSort.h"


void BitonicSort::sortiraj(Niz * niz)
{
	int pow = 1, i = 0, temp;
	int array_size = niz->brElemenata();

	while (pow <= array_size) pow = pow << 1;
	pow = pow >> 1;
	int size = pow;
	//making the bitonic sequence
	int inc = 1, dec;
	bool asc = true;
	//inc
	while (inc< pow){	
		asc = true;
		i = 0;
		int cnt = 0;
		while (i < size) {
			brojKoraka++;
			cnt++;
			int ind1 = asc ? i : i + inc;
			int ind2 = asc ? i + inc : i;
			if ((*niz)[ind1]>(*niz)[ind2]) zameni(niz, ind1, ind2);
			if (cnt == inc) {
				i += inc;
				cnt = 0;
				asc = !asc;
			}
			i++;	
		}

		//going back to 1
		if (inc != 1) {
			dec = inc>>1;
			int sstep=inc<<1;
			int step;
			while (dec > 0) {
				step = sstep;
				asc = true;
				i = 0;
				int cnt = 0;
				while (i < size) {
					brojKoraka++;
					cnt++;
					int ind1 = asc ? i : i + dec;
					int ind2 = asc ? i + dec : i;
					if ((*niz)[ind1]>(*niz)[ind2]) zameni(niz, ind1, ind2);
					if (cnt == dec) {
						i += dec;
						cnt = 0;
					}
					i++;
					if (i >= step) { 
						asc = !asc; 
						step+=sstep;
					}
				}
				dec = dec >> 1;
			}
		}
		inc = inc << 1;
	}
	
	//sort rest of the array (size-pow elements)
	for (i = size; i < array_size; i++) {
		temp = (*niz)[i];
		int j = 0;
		while ((*niz)[j] < temp) j++;
		for (int k = i; k > j; k--) (*niz)[k] = (*niz)[k - 1];
		(*niz)[j] = temp;
	}
}
