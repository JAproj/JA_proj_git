#include "stdafx.h"
#include "TworzenieWatkow.h"

TworzenieWatkow::TworzenieWatkow() {

}

void TworzenieWatkow::watekAsm(vector<vector<int>> vecDane, ObslugaDll* dll, promise<vector<vector<int>>>& prms) {

	wynik.clear();
	for (int i = 0; i < vecDane.size(); i++) {
		int* tabDane = new int[vecDane[i].size()];
		for (int j = 0; j < vecDane[i].size(); j++) {
			tabDane[j] = vecDane[i][j];
		}
		int* tmpWynik = new int[vecDane[i].size()];
		tmpWynik = dll->obliczeniaDllAsm(vecDane[i].size(), tabDane);
		vector<int> vecTmp;
		for (int j = 0; j < vecDane[i].size(); j++) {
			vecTmp.push_back(tmpWynik[j]);
		}
		wynik.push_back(vecTmp);
		vecTmp.clear();
	}

	prms.set_value(wynik);
}



void TworzenieWatkow::watekC(vector<vector<int>> vecDane, ObslugaDll* dll, promise<vector<vector<int>>>& prms) {

	wynik.clear();
	for (int i = 0; i < vecDane.size(); i++) {
		int* tabDane = new int[vecDane[i].size()];
		for (int j = 0; j < vecDane[i].size(); j++) {
			tabDane[j] = vecDane[i][j];
		}
		int* tmpWynik = new int[vecDane[i].size()];
		tmpWynik = dll->obliczeniaDllC(vecDane[i].size(), tabDane);
		vector<int> vecTmp;
		for (int j = 0; j < vecDane[i].size(); j++) {
			vecTmp.push_back(tmpWynik[j]);
		}
		wynik.push_back(vecTmp);
		vecTmp.clear();
	}

	prms.set_value(wynik);
}
