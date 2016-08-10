// Michael Bechard
// 3/14/12
// Poly.cpp
// This function checks to see that
// (X + a)^n = X^n + a (mod (X^r - 1),n)
// where n is "prime", r is "modr", and
// a runs from 1 to "bound".

#include"Poly.h"
#include<iostream>

bool Poly(ZZ prime, ZZ modr, ZZ bound)
{

	ofstream dout; //File output
	dout.open("1_mill_to_1,100,000.txt", fstream::app);

	ZZ_p::init(prime); // Sets modulus as "prime"

	// Prepare modulus polynomial

	ZZ_pX modPoly;
	long modr2;
	conv(modr2,modr);
	SetCoeff(modPoly,modr2,1); // 1*X^modr
	SetCoeff(modPoly, 0, -1); //modPoly = X^modr -1
	ZZ_pXModulus mod(modPoly);
	
	// Now declare polynomials
	ZZ integer; // Used to store a
	ZZ_pX bigx; // (x + a)^n
	SetCoeff(bigx,1,1); // Initialize to 1*X^1
	ZZ_pX big;

	ZZ smlBnd; // Used for small polynomial
	long smlBnd2; // formatting
	smlBnd = prime%modr;
	conv(smlBnd2,smlBnd); // formatting, need type long
	ZZ_pX small; // x^n + a
	SetCoeff(small,smlBnd2); // 1*X^prime%modr

	for (integer = 1; integer<=bound; integer++)
	{ // Loop through all values for a.
		
		SetCoeff(bigx, 0, to_long(integer)); // big = X^1 + integer
		SetCoeff(small, 0, to_long(integer)); // small = X^prime%modr + integer
		
		// Exponentiate. Takes ten thousand years.
		big = PowerMod(bigx, prime, mod); // Bam.
		//cout << "Done with polynomial with integer of " << integer << endl;


		// Check if big == small.
		if (big != small && integer>1)
		{
			dout << prime << " is a false pos, modr: " << modr << endl;
			//cout << "Polynomial failed with integer of " << integer << endl;
			//return false;
		}

		if(big!=small)
		{ // Failed, go to next number
			integer = bound+1;
		}

	} // Checking all integers loop.

	dout.close();

	return true; // The number is prime!
}

/* Another implementation

ZZ_p::init(prime); // Sets modulus as "prime"

	// Prepare modulus polynomial

	ZZ_pX modPoly;
	long modr2;
	conv(modr2,modr);
	SetCoeff(modPoly,modr2,1); // 1*X^modr
	SetCoeff(modPoly, 0, -1); //modPoly = X^modr -1
	ZZ_pE::init(modPoly);
	
	// Now declare polynomials
	ZZ integer; // Used to store a
	ZZ_pX bigx; // (x + a)^n
	SetCoeff(bigx,1,1); // Initialize to 1*X^1
	ZZ_pE big;

	ZZ smlBnd; // Used for small polynomial
	long smlBnd2; // formatting
	smlBnd = prime%modr;
	conv(smlBnd2,smlBnd); // formatting, need type long
	ZZ_pX smallx; // x^n + a
	SetCoeff(smallx,smlBnd2); // 1*X^prime%modr
	ZZ_pE small;
	

	for (integer = 1; integer<bound; integer++)
	{ // Loop through all values for a.
		
		SetCoeff(bigx, 0, to_long(integer)); // big = X^1 + integer
		SetCoeff(smallx, 0, to_long(integer)); // small = X^prime%modr + integer
		
		conv(big,bigx); // Convert left side to ZZ_pE
		conv(small,smallx); // Convert right side to ZZ_pE
		
		// Exponentiate. Takes ten thousand years.
		big = power(big, prime); // Bam.
		cout << "Done with polynomial with integer of " << integer << endl;
*/