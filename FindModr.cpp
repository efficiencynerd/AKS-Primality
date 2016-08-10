// Michael Bechard
// 2/27/12
// This function finds the smallest r such that
// the order of r modulo the input ("prime")
// is greater than log(prime) base 2 squared.

#include"FindModr.h"


ZZ FindModr(ZZ prime)
{
	RR primesq; // log^2(prime)
	RR num; // to get log base 2
	num = 2;
	ZZ modr; // r in prime^k = 1(mod(r))
	ZZ order; // k in prime^k = 1(mod(r))
	ZZ temp; // Used to hold order starting point (counts up from here)
	ZZ tot; // Totient
	ZZ two;
	two = 2;


	conv(primesq,prime);

	// Set primesq equal to log^2(prime)
	primesq = log(primesq)/log(num)*log(primesq)/log(num);

	// Set order higher than primesq, also store in temp
	conv(order,primesq);
	order = order+1;
	temp = order;
//	cout << "log^2 value (ceiling) is " << temp << endl;

	//
	// modr starts at log^2(prime) + 2
	for(modr = temp+1; true; modr++)
	{ // Loops until proper r value is found.
		// Should never kick out due to the loop condition.

		tot = FindTot(modr);

		// Order starts at log^2(prime) + 1
		for(order = temp;order <= tot/two; order++)
		{ // Check any possible order less than half the totient
			if (tot%order==0)
			{ // If order is a factor of totient
				if(PowerMod(prime%modr,order,modr)==1)
				{ // Check if "order" is actually an order of (prime) modulo (mod)
	//				cout << "I was here." << endl;
					goto end; // Break both loops.
				}
			}
		} // end checking order values up to tot/2
		
		// Now check when order = tot
		if(tot>=temp)
		{
			order = tot; // automatically means tot%order == 0
			if(PowerMod(prime%modr,order,modr)==1)
			{ // Check if "order" is actually an order of (prime) modulo (mod)
				goto end; // Break both loops.
			}
		}

	} // end checking modr values
end:
	//cout << "Modr value is " << modr << endl;
/*	cout << "the order of modr modulo prime is " << order << endl;
	cout << "Check: " << PowerMod(prime%modr,order,modr) << endl;
	cout << "Totient is " << tot << endl;
*/
	return modr;
}; // End FindModr