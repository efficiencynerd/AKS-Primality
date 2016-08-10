// Michael Bechard
// 2/21/2012
// This program implements the AKS primality test.
// It utilizes the NTL library for large numbers.


#include<iostream>
#include<NTL/ZZ.h> // Integer library
#include<NTL/RR.h> // Float library
#include<cmath>
#include<stdlib.h>
#include<time.h>
#include<fstream>

#include"isPower.h"
#include"FindModr.h"
#include"FindTot.h"
#include"Gcd.h"
#include"CheckGcd.h"
#include"Poly.h"
// #include"RedoPoly.h" Trash

using namespace NTL;

using namespace std;

int main()
{
	
	ZZ prime; // Number entered
	RR flprime; // Used where float is needed
	bool isPrime = true; // Is the number a prime?
	ZZ modr; // Used to find order of r modulo n.
	ZZ tot; // Euler's totient
	double logn; // Used to find log of prime
	ZZ bound;  // Upper bound for polynomial expansion
	float time;

	// Set up data log
//	ofstream dout;
//	dout.open("log.txt", fstream::app);


	cout << "This function determines if your number is a prime." << endl
		<< "The cool part is, it does so with super speed." << endl
		<< "Enter your number to check:" << endl;
	cin >> prime;
	
	cout << "Running..." << endl << "Output format: number, modr value, and integer that failed."
		<< endl;

//1	for(prime=1000000;prime<=1100000;prime++)
//1	{
		while (prime>0)
		{ // Loops until zero or negative value encountered
			time = GetTime();
			cout << "Started at " << time << "s." << endl;

			conv(flprime,prime); // Converts prime to float, stored in flprime
			cout << "Checking if the number is prime..." << endl;
			isPrime = IsPower(flprime); // Checks if the number is a power.
			// If it is a power, returns false; otherwise returns true.
			if(!isPrime)
			{ // Is the number composite?
				cout << "Number is a power, thus composite." << endl;
				time = GetTime() - time;
//				dout << "The number " << prime << endl<< " is a power. It took " 
//					<< time << " seconds." << endl;
				cout << "Ended at " << GetTime() << "s." << endl;
				goto end;
			}
			cout << "Number not a power." << endl;
	
			// Find the smallest r such that
			// the order of n modulo r is greater than log(n) squared.
			cout << "Finding modr..." << endl;
			modr = FindModr(prime);
	
			// Check any a<=modr, make sure gcd(a,prime) == 1.
			cout << "Checking gcd of (a,prime) for any a<=modr..." << endl;
	
			isPrime = CheckGcd(prime,modr); // Returns false if composite.
			if(!isPrime)
			{ // Found a factor.
				time = GetTime() - time;
//				dout << "The number " << prime << endl << " is composite by gcd check.  It took " 
//					<< time << " seconds." << endl;
				cout << "Ended at " << GetTime() << "s." << endl;
				goto end;
			}

			// From the last step, do a quick check.
			if (prime <= modr)
			{
				cout << "Number is prime, it is less than modr." << endl;
				time = GetTime() - time;
//				dout << "The number " << prime << endl << " is prime, less than modr. It took " 
//					<< time << " seconds." << endl;
				cout << "Ended at " << GetTime() << "s." << endl;
				goto end;
			}

			cout << "Building polynomials..." << endl;

			// Find bound for polynomial expansion
			tot = FindTot(modr);
			tot = SqrRoot(tot);
			logn = log(prime);
			conv(bound,logn);
			bound *= tot; // Upper Bound, at floor(sqrt(tot(modr))*log(prime))
			cout << "highest polynomial is " << bound << endl;

			// Build polynomials and check for all integers <= floor(sqrt(tot(modr))*log(prime))
			isPrime = Poly(prime,modr,bound); // returns true if prime.

			if (!isPrime)
			{
				time = GetTime() - time;
//				dout << "The number " << prime << endl << " is composite by polynomial. It took " 
//					<< time << " seconds." << endl;
				cout << "Ended at " << GetTime() << "s." << endl;
			}
			else
			{
				cout << "Your number passed the test.  It is thus prime." << endl;
				time = GetTime() - time;
//				dout << "The number " << prime << endl << " is a prime. It took " 
//					<< time << " seconds." << endl;
				cout << "Ended at " << GetTime() << "s." << endl;
			}
	end:
//			dout << endl;
			cout << "Your number took " << time << " seconds to compute." << endl << endl;
			cout << "Enter another number, or 0 to end:" << endl;
			cin >> prime;
		} // End main program while
//1		cout << "Done with " << prime << endl;
//1	}

//	dout.close();
	
	cout << "Bye." << endl;
	
	system("PAUSE");
	return 0;
}