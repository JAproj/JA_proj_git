#include "stdafx.h"
#include "ObslugaDanych.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>

using namespace std;

ObslugaDanych::ObslugaDanych()
{
}

vector<vector<int>> ObslugaDanych::pobierzDane()
{
	fstream plik;
	vector<int> vecTmp;
	try {
		plik.open("dane.txt", std::ios::in);
		if (plik.good())
		{
			string str;
			int i = 0;
			while (getline(plik, str))
			{
				istringstream ss(str);
				int num;
				while (ss >> num)
				{
					vecTmp.push_back(num);
				}
				vecDane.push_back(vecTmp);
				vecTmp.clear();
			}
			plik.close();

			if (vecDane.size() == 0) {
				MessageBox(NULL, L"Nie mo¿na pobraæ danych!", L"B³¹d", MB_ICONINFORMATION | MB_OK);
				exit(1);
			}

			return vecDane;
		}
		else {
			MessageBox(NULL, L"Nie mo¿na otworzyæ pliku z danymi!", L"B³¹d", MB_ICONINFORMATION | MB_OK);
			exit(1);
		}
	}
	catch (...) {
		MessageBox(NULL, L"Nie mo¿na otworzyæ pliku z danymi!", L"B³¹d", MB_ICONINFORMATION | MB_OK);
		exit(1);
	}
}

void ObslugaDanych::zapiszDane(vector<vector<vector<int>>> wynik, unsigned __int64 czas, int iloscWatkow, string nazwaPlik)
{
	fstream plik;
	try {
		plik.open(nazwaPlik, std::ios::out);
		if (plik.good())
		{
			for (int i = 0; i < wynik.size(); i++) {
				for (int j = 0; j < wynik[i].size(); j++) {
					for (int k = 0; k < wynik[i][j].size(); k++) {
						plik << wynik[i][j][k] << " ";
					}
					plik << endl;
				}
			}
			plik << "Iloœæ w¹tków: " << iloscWatkow << endl;
			plik << "Czas sortowania: " << czas << " milisekund" << endl;
			plik.close();
		}
		else {
			MessageBox(NULL, L"Nie mo¿na zapisaæ wyniku do pliku!", L"B³¹d", MB_ICONINFORMATION | MB_OK);
		}
	}
	catch (...) {
		MessageBox(NULL, L"Nie mo¿na zapisaæ wyniku do pliku!", L"B³¹d", MB_ICONINFORMATION | MB_OK);
	}

}

