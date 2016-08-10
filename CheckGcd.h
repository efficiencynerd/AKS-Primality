#ifndef _CHECKGCD_H // if not defined
#define _CHECKGCD_H // define MyHeader

#include<iostream>
#include<NTL/ZZ.h> // Integer library
#include<stdlib.h>

#include"Gcd.h"

using namespace NTL;
using namespace std;

bool CheckGcd(ZZ prime, ZZ modr);

#endif