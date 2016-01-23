#ifndef OBSLUGAWATKOW_H
#define OBSLUGAWATKOW_H
#include "stdafx.h"
#include "ObslugaDll.h"
#include "TworzenieWatkow.h"
#include <vector>

class ObslugaWatkow
{
private:
	ObslugaDll* dll = new ObslugaDll();
	TworzenieWatkow* watek = new TworzenieWatkow();
	vector<vector<int>> wynik;
	vector<vector<int>> wynikPosredni;
	vector<vector<int>> danePosrednie;
	vector<int> dlugoscTabeli;
	vector<vector<vector<int>>> vecWynikiPosrednie;
	unsigned long long czas;

public:
	ObslugaWatkow();

	vector<vector<vector<int>>> noweWatkiAsm(int, int, vector<vector<int>>);
	vector<vector<vector<int>>> noweWatkiC(int, int, vector<vector<int>>);

};

#endif /* OBSLUGAWATKOW_H */