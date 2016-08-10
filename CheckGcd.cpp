// Michael Bechard
// 3/14/12
// This function checks the Gcd of "prime" and all 
// numbers up to "modr". If the Gcd is not 1, the
// function outputs the result and returns false.

#include"CheckGcd.h"

bool CheckGcd(ZZ prime, ZZ modr)
{
	int sieve [47] = {6,6,2,6,4,2,6,4,6,8,4,2,4,2,
					4,8,6,4,6,2,4,6,2,6,6,4,2,4,
					6,2,6,4,2,6,10,2,10,2,4,2,4,
					6,2,6,4,2,4}; // Sieves out 2,3,5, and 7. Starts at the prime 47.
	int primes [15] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47}; // Primes up through 47.
	ZZ each; // Used to check each number below modr
	bool isPrime; // Could the number still be a prime?

	for(register int i = 0; i<15;i++)
	{ // Check Gcd using first primes.
		each = primes[i];

		if(each > modr || each >= prime)
			return true;

		isPrime = Gcd(prime,each);

		if(!isPrime)
		{ // Number is composite.
			cout << "Number is composite by Gcd with " << each << endl;
			return false;
		}
	} // Finished checking Gcd for first primes.

	// Check remaining numbers less than modr, using sieve.
	each = 53;
	for(register int j = 1; each<=modr;j++)
	{
		if(each >= prime)
			return true;
	
		isPrime = Gcd(prime,each);

		if(!isPrime)
		{ // Number is composite.
			cout << "Number is composite by Gcd with " << each << endl;
			return false;
		}
		each += sieve[j%47];
	} // No number less than modr is a factor of prime.

	return true;
}