#include "stdafx.h"
#include "ObslugaWatkow.h"
#include <iostream>
#include <stdio.h>
#include <thread>
#include <future> // do pobierania returna z w¹tku
#include <windows.h>

using namespace std;

ObslugaWatkow::ObslugaWatkow()
{
}

vector<vector<vector<int>>> ObslugaWatkow::noweWatkiAsm(int iloscWatkow, int iloscDanych, vector<vector<int>> dane)
{

	vecWynikiPosrednie.clear();
	thread *tt = new thread[iloscWatkow];
	promise<vector<vector<int>>> *prms = new promise<vector<vector<int>>>[iloscWatkow];
	future<vector<vector<int>>> *ftr = new future<vector<vector<int>>>[iloscWatkow];

	for (int i = 0; i < iloscWatkow; i++) {
		ftr[i] = prms[i].get_future();
	}

	int licznik = 0;
	int* ileDanychNaPowtorzeniePetli = new int[iloscWatkow];
	int ileDanychWPetli = int(iloscDanych / iloscWatkow);
	double reszta = fmod(iloscDanych, iloscWatkow);
	if (reszta != 0.0) {	//gdy reszta = 0 to zawsze laduj po ileDanychWPetli do ka¿dego w¹tku
		while (reszta > 0) {
			ileDanychNaPowtorzeniePetli[licznik] = ileDanychWPetli + 1;
			reszta = reszta - 1;
			licznik++;
		}
		for (int i = licznik; i < iloscWatkow; i++) {
			ileDanychNaPowtorzeniePetli[i] = ileDanychWPetli;
		}
	}
	else {
		for (int i = 0; i < iloscWatkow; i++) {
			ileDanychNaPowtorzeniePetli[i] = ileDanychWPetli;
		}
	}

	licznik = 0;
	if (dll->dolaczanieDllAsm()){
		for (int i = 0; i < iloscWatkow; i++) {
			for (int j = 0; j < ileDanychNaPowtorzeniePetli[i]; j++) {
				danePosrednie.push_back(dane[licznik]);
				licznik++;
			}
			tt[i] = thread(&TworzenieWatkow::watekAsm, watek, danePosrednie, dll, ref(prms[i]));
			vecWynikiPosrednie.push_back(ftr[i].get());
			tt[i].join();
			danePosrednie.clear();
		}
	}

	dll->odloczanieDllAsm();
	return vecWynikiPosrednie;
}

vector<vector<vector<int>>> ObslugaWatkow::noweWatkiC(int iloscWatkow, int iloscDanych, vector<vector<int>> dane)
{

	vecWynikiPosrednie.clear();
	thread *tt = new thread[iloscWatkow];
	promise<vector<vector<int>>> *prms = new promise<vector<vector<int>>>[iloscWatkow];
	future<vector<vector<int>>> *ftr = new future<vector<vector<int>>>[iloscWatkow];

	for (int i = 0; i < iloscWatkow; i++) {
		ftr[i] = prms[i].get_future();
	}

	int licznik = 0;
	int* ileDanychNaPowtorzeniePetli = new int[iloscWatkow];
	int ileDanychWPetli = int(iloscDanych / iloscWatkow);
	double reszta = fmod(iloscDanych, iloscWatkow);
	if (reszta != 0.0) {	//gdy reszta = 0 to zawsze laduj po ileDanychWPetli do ka¿dego w¹tku
		while (reszta > 0) {
			ileDanychNaPowtorzeniePetli[licznik] = ileDanychWPetli + 1;
			reszta = reszta - 1;
			licznik++;
		}
		for (int i = licznik; i < iloscWatkow; i++) {
			ileDanychNaPowtorzeniePetli[i] = ileDanychWPetli;
		}
	}
	else {
		for (int i = 0; i < iloscWatkow; i++) {
			ileDanychNaPowtorzeniePetli[i] = ileDanychWPetli;
		}
	}

	licznik = 0;
	if (dll->dolaczanieDllC()){
		for (int i = 0; i < iloscWatkow; i++) {
			for (int j = 0; j < ileDanychNaPowtorzeniePetli[i]; j++) {
				danePosrednie.push_back(dane[licznik]);
				licznik++;
			}
			tt[i] = thread(&TworzenieWatkow::watekC, watek, danePosrednie, dll, ref(prms[i]));
			vecWynikiPosrednie.push_back(ftr[i].get());
			tt[i].join();
			danePosrednie.clear();
		}
	}

	dll->odloczanieDllC();
	return vecWynikiPosrednie;
}
