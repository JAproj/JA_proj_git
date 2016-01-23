#ifndef OBSLUGADLL_H
#define OBSLUGADLL_H

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
using namespace std;

class ObslugaDll {

private:
	//	dynamiczne ³adowanie dll Asm
	typedef int* (_stdcall *addFuncAsm)(int, int*);		//
	addFuncAsm MyFuncAsm;
	HINSTANCE hLibAsm;
	// dynamiczne ³adowanie dll C
	typedef int* (_stdcall *addFuncC)(int, int*);
	addFuncC MyFuncC;
	HINSTANCE hLibC;

public:

	bool dolaczanieDllAsm();
	int* obliczeniaDllAsm(int, int*);
	void odloczanieDllAsm();
	bool dolaczanieDllC();
	int* obliczeniaDllC(int, int*);
	void odloczanieDllC();
};

#endif /* OBSLUGADLL_H */