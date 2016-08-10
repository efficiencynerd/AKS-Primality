#ifndef _FINDMODR_H // if not defined
#define _FINDMODR_H // define MyHeader

#include<iostream>
#include<NTL/ZZ.h> // Integer library
#include<NTL/RR.h> // Float library
#include<cmath>
#include<stdlib.h>

#include"FindTot.h"

using namespace NTL;

ZZ FindModr(ZZ prime);

#endif