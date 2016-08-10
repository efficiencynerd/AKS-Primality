#ifndef _POLY_H // if not defined
#define _POLY_H // define MyHeader

#include<iostream>
#include<fstream>
#include<NTL/ZZ.h> // Integer library
#include<NTL/ZZ_p.h> // Mod p library
#include<NTL/ZZ_pE.h> // Polynomial library
#include<NTL/ZZ_pX.h>
#include<NTL/ZZ_pEX.h>

using namespace NTL;
using namespace std;

bool Poly(ZZ prime, ZZ modr, ZZ bound);

#endif