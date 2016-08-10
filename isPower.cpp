// Michael Bechard
// 2/27/12
// This function determines if a number is
// a power and thus is not a prime.
// if the number is determined to be a power,
// the function returns false (the number is not prime);
// if no power is found, it returns true, as 
// the number could still be a prime.

#include"isPower.h"

bool IsPower(RR flprime)
{
	ZZ num; // Used for mod 1
	RR root; // where root is stored; value of 2 so loop will work
	RR two;
	two = 2;
	ZZ i;
	long j;
	RR pwr;  // Power used to find next root
	RR rootflr; // Uses floor function on root

	RR::SetPrecision(1000);

	int sieve [47] = {6,6,2,6,4,2,6,4,6,8,4,2,4,2,
					4,8,6,4,6,2,4,6,2,6,6,4,2,4,
					6,2,6,4,2,6,10,2,10,2,4,2,4,
					6,2,6,4,2,4}; // Sieves out 2,3,5, and 7. Starts at the prime 47.
	int primes [15] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47}; // Primes up through 47.

	// Use sieve to check prime roots.
	for (j = 0; j<15; j++)
	{ // Find each root greater than 2,
		// check if any is integer.

		i = primes[j];

		conv(pwr,i);
		pwr = 1/pwr; // Power to use to find root
		root = pow(flprime,pwr);
		rootflr = trunc(root); // Truncates root
		
		if (rootflr == root)
		{
			cout << "Number is " << root << "^" << i << "." << endl;
			return false; // Found a power.
		}
	}
	// Didn't find a root less than 47

	for (j = 0; root>two; j++)
	{ // Find each root greater than 2,
		// check if any is integer.

		i += sieve[j%47];

		conv(pwr,i);
		pwr = 1/pwr; // Power to use to find root
		root = pow(flprime,pwr);
		rootflr = trunc(root); // Truncates root
		
		if (rootflr == root)
		{
			cout << "Number is " << root << "^" << i << "." << endl;
			return false; // Found a power.
		}
	}
	// Didn't find a power
	return true;
}; // End IsPower
