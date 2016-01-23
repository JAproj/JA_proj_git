#include "stdafx.h"

#include <windows.h>
#include "ObslugaDll.h"

using namespace std;

bool ObslugaDll::dolaczanieDllAsm()
{
	if ((hLibAsm = LoadLibrary(L"JAAsm.dll")) != NULL) {
		MyFuncAsm = (addFuncAsm)GetProcAddress(hLibAsm, "MyFuncAsm");
		if (MyFuncAsm != NULL) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

int* ObslugaDll::obliczeniaDllAsm(int ilosc, int* dane)
{
	return MyFuncAsm(ilosc, &(dane[0]));
}

void ObslugaDll::odloczanieDllAsm()
{
	FreeLibrary(hLibAsm);
}

bool ObslugaDll::dolaczanieDllC()
{
	if ((hLibC = LoadLibrary(L"JAC.dll")) != NULL) {
		MyFuncC = (addFuncC)GetProcAddress(hLibC, "MyFuncC");
		if (MyFuncC != NULL) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

int* ObslugaDll::obliczeniaDllC(int ilosc, int* dane)
{
	return MyFuncC(ilosc, dane);
}

void ObslugaDll::odloczanieDllC()
{
	FreeLibrary(hLibC);
}
