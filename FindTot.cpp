// Michael Bechard
// 3/14/2012
// This program finds the totient of the input.
// Input and output are both type ZZ from the NTL library.

#include"FindTot.h"
#include<iostream>

ZZ FindTot(ZZ modr)
{
	ZZ tot;
	tot = 1;
	ZZ factor; // Factor of totient
	ZZ root; // Square root of current modr
	root = SqrRoot(modr);
	long pwr;  // Factor to this power
	bool found = false; // did we find the highest power of the factor?
	int sieve [47] = {6,6,2,6,4,2,6,4,6,8,4,2,4,2,
					4,8,6,4,6,2,4,6,2,6,6,4,2,4,
					6,2,6,4,2,6,10,2,10,2,4,2,4,
					6,2,6,4,2,4}; // Sieves out 2,3,5, and 7. Starts at the prime 47.
	int primes [15] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47}; // Primes up through 47.


	for (register int i = 0; i<15;i++)
	{ // Check primes through 47
		factor = primes[i];
		if (modr%factor==0)
		{ // factor is a factor of modr
			for (pwr = 2; !found; pwr++)
			{ // find highest power of factor that is a factor of totient
				if (modr%power(factor,pwr)!=0)
				{
					tot *= (power(factor,pwr-1)-power(factor,pwr-2)); // Increase totient
					modr /= power(factor,pwr-1); // Remove factor we just found from modr
	//				cout << "Found factor " << factor << "^" << pwr-1 << endl;
					pwr = 1; // Reset pwr value
					found = true;				
				}
			} // end increase pwr
			found = false; // Reset found value
		}
	}

	// Find the remaining factors, using the sieve pattern
	// (improves speed by 50 percent over checking odd numbers)
	factor = 47; // Start factor where sieve starts
	for (register int j = 0; modr != 1; j++)
	{  // Find all remaining factors of modr
		factor += sieve[j%47]; // Loops through sieve

		if (factor > root)
		{ // This means modr (divided by previously found factors) is the only remaining factor.
			factor = modr;
		}
		
		if (modr%factor==0)
		{ // factor is a factor of modr
			for (pwr = 2; !found; pwr++)
			{ // find highest power of factor that is a factor of totient
				if (modr%power(factor,pwr)!=0)
				{
					tot *= (power(factor,pwr-1)-power(factor,pwr-2)); // Increase totient
					modr /= power(factor,pwr-1); // Remove factor we just found from modr
					root = SqrRoot(modr);
	//				cout << "Found factor " << factor << "^" << pwr-1 << endl;
					pwr = 1; // Reset pwr value
					found = true;
				}
			} // end increase pwr
			found = false;  // Reset found value
		}
		
	} // End finding all factors
	return tot;
}