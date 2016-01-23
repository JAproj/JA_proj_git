// JAApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>

#include "ObslugaDanych.h"
#include "ObslugaWatkow.h"
#include "Zasoby.h"
#include "CPUInfo.h"

using namespace std;


LPSTR NazwaKlasy = "JAProjekt";
MSG Komunikat;
HWND hPrzyciskAsm;
HWND hPrzyciskC;
HWND hDane;
HWND hWynik;
HWND hTextDane;
HWND hTextWynik;
HWND hWatkiWybor;
HWND hWatkiIlosc;
HWND hWatkiOdczyt;
HWND hCzas;

//do pobrania ilosci watkow
DWORD dlugosc;
LPWSTR Bufor;
int iloscWatkow = 1;

//zapamiêtanie która dll
BOOL flagaASM = false;
BOOL flagaC = false;

//mierzenie czasu
//Jest to konstrukcja pod Borlanda Buildera 6 C++.
LARGE_INTEGER start, stop, freq;
unsigned __int64  start1, stop1, freq1;
unsigned long long czas;

CPUInfo* cpuInfo;
ObslugaDanych* dane;
ObslugaWatkow* watek;
vector<vector<int>> vecDane;
vector<vector<vector<int>>> wynikiC;
vector<vector<vector<int>>> wynikiAsm;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
std::wstring s2ws(const std::string& s);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	cpuInfo = new CPUInfo();
	dane = new ObslugaDanych();
	watek = new ObslugaWatkow();
	vecDane = dane->pobierzDane();

	// WYPE£NIANIE STRUKTURY
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = LPCWSTR(NazwaKlasy);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// REJESTROWANIE KLASY OKNA
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Wysoka Komisja odmawia rejestracji tego okna!", L"Niestety...", MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	// TWORZENIE OKNA
	HWND hwnd;

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, LPCWSTR(NazwaKlasy), L"Projekt JA - Sortowanie B¹belkowe", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 720, 680, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Okno odmówi³o przyjœcia na œwiat!", L"Ale kicha...", MB_ICONEXCLAMATION);
		return 1;
	}

	//Tworzenie przycisków
	hPrzyciskAsm = CreateWindowEx(1, L"BUTTON", L"Dll Asm", WS_CHILD | WS_VISIBLE | BS_CHECKBOX | WS_BORDER,
		50, 10, 150, 30, hwnd, HMENU(ID_DLLASM), hInstance, NULL);
	hPrzyciskC = CreateWindowEx(1, L"BUTTON", L"Dll C", WS_CHILD | WS_VISIBLE | BS_CHECKBOX | WS_BORDER,
		210, 10, 150, 30, hwnd, HMENU(ID_DLLC), hInstance, NULL);
	hPrzyciskC = CreateWindowEx(1, L"BUTTON", L"ZatwierdŸ", WS_CHILD | WS_VISIBLE | WS_BORDER,
		330, 55, 100, 30, hwnd, HMENU(ID_WATKIZATWIERDZ), hInstance, NULL);

	//Tworzenie pól tekstowch
	hDane = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_READONLY,
		50, 120, 600, 220, hwnd, (HMENU)ID_DANE, hInstance, NULL);
	hWynik = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_READONLY,
		50, 380, 600, 220, hwnd, (HMENU)ID_WYNIK, hInstance, NULL);
	hTextDane = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE,
		50, 100, 600, 20, hwnd, (HMENU)ID_TEXTDANE, hInstance, NULL);
	hTextWynik = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE,
		50, 360, 600, 20, hwnd, (HMENU)ID_TEXTWYNIK, hInstance, NULL);
	hWatkiIlosc = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", NULL, WS_CHILD | WS_VISIBLE,
		50, 60, 250, 20, hwnd, (HMENU)ID_WATKIILOSC, hInstance, NULL);
	hWatkiWybor = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL, WS_CHILD | WS_VISIBLE,
		300, 60, 25, 20, hwnd, (HMENU)ID_WATKIWYBOR, hInstance, NULL);
	hWatkiOdczyt = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", NULL, WS_CHILD | WS_VISIBLE,
		380, 15, 200, 20, hwnd, (HMENU)ID_WATKIODCZYT, hInstance, NULL);
	hCzas = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", NULL, WS_CHILD | WS_VISIBLE,
		50, 610, 600, 20, hwnd, (HMENU)ID_CZAS, hInstance, NULL);

	//Wype³nianie pól tekstowych
	std::string tmp0 = "Dostêpne w¹tki: " + to_string(cpuInfo->pobierzIloscWatkowZProcesora());
	std::wstring tmp1 = s2ws(tmp0);
	SetWindowText(hWatkiOdczyt, (LPCWSTR)tmp1.c_str());
	SetWindowText(hWatkiIlosc, L"Podaj iloœæ w¹tków: ");
	SetWindowText(hTextDane, L"Dane:");
	std::string txtDane = "";
	std::string tmp = "";
	std::wstring tekst;
	for (int i = 0; i < vecDane.size(); i++) {
		for (int j = 0; j < vecDane[i].size(); j++) {
			tmp += (to_string((int)vecDane[i][j]) + " ");
		}
		txtDane += (tmp + "\r\n");
		tmp = "";
	}
	tekst = s2ws(txtDane);
	SetWindowText(hDane, (LPCWSTR)tekst.c_str()); //wyswietlenie danych
	SetWindowText(hTextWynik, L"Wynik:");

	ShowWindow(hwnd, nCmdShow); // Poka¿ okienko...
	UpdateWindow(hwnd);

	// Pêtla komunikatów
	while (GetMessage(&Komunikat, NULL, 0, 0))
	{
		TranslateMessage(&Komunikat);
		DispatchMessage(&Komunikat);
	}
	return Komunikat.wParam;
}

// OBS£UGA ZDARZEÑ
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (wParam) {

		case ID_DLLASM:
			if (CheckDlgButton(hwnd, ID_DLLASM, BST_CHECKED)) {
				flagaASM = true;
				CheckDlgButton(hwnd, ID_DLLC, BST_UNCHECKED);
				flagaC = false;
				SetWindowText(hWynik, L"");
				SetWindowText(hCzas, L"");
			};
			break;

		case ID_DLLC:
			if (CheckDlgButton(hwnd, ID_DLLC, BST_CHECKED)) {
				flagaC = true;
				CheckDlgButton(hwnd, ID_DLLASM, BST_UNCHECKED);
				flagaASM = false;
				SetWindowText(hWynik, L"");
				SetWindowText(hCzas, L"");
			};
			break;

		case ID_WATKIZATWIERDZ: 
			dlugosc = GetWindowTextLength(hWatkiWybor);
			Bufor = (LPWSTR)GlobalAlloc(GPTR, dlugosc + 1);
			GetWindowText(hWatkiWybor, Bufor, dlugosc + 1);
			iloscWatkow = _wtoi(Bufor);
			if (iloscWatkow == 0 || iloscWatkow > vecDane.size() || iloscWatkow > 64) {
				if (iloscWatkow > 64) {
					MessageBox(hwnd, L" Podaj poprawn¹ iloœæ w¹tków <0;64>!!!", L"B³¹d!", MB_ICONINFORMATION);
				}
				else {
					MessageBox(hwnd, L"Iloœæ w¹tków nie mo¿e byæ wiêksza ni¿ liczba wierszy z danymi. Podaj poprawn¹ iloœæ w¹tków!!!", L"B³¹d!", MB_ICONINFORMATION);
				}
			}
			else {

				std::string txtWynik = "";
				std::string tmp = "";
				std::wstring tekst = s2ws("");

				if (flagaASM){
					QueryPerformanceFrequency(&freq);
					QueryPerformanceCounter(&start);
					wynikiAsm = watek->noweWatkiAsm(iloscWatkow, vecDane.size(), vecDane);
					QueryPerformanceCounter(&stop);
					start1 = start.QuadPart;	//Represents a 64 - bit signed integer.
					stop1 = stop.QuadPart;
					freq1 = freq.QuadPart;
					czas = (((stop1)-(start1)) * pow(10, 3)) / freq1;
					txtWynik = "Czas sortowania - Dll Asembler: " + std::to_string(czas) + " milisekund";
					tekst = s2ws(txtWynik);
					SetWindowText(hCzas, (LPCWSTR)tekst.c_str());
					txtWynik = "";
					tekst = s2ws("");
					for (int i = 0; i < wynikiAsm.size(); i++) {
						for (int j = 0; j < wynikiAsm[i].size(); j++) {
							for (int k = 0; k < wynikiAsm[i][j].size(); k++) {
								tmp += (to_string((int)wynikiAsm[i][j][k]) + " ");
							}
							txtWynik += (tmp + "\r\n");
							tmp = "";
						}
					}
					tekst = s2ws(txtWynik);
					SetWindowText(hWynik, (LPCWSTR)tekst.c_str()); //wyswietlenie wyniku
					dane->zapiszDane(wynikiAsm, czas, iloscWatkow, "wynikiAsm.txt");
				}

				if (flagaC) {
					QueryPerformanceFrequency(&freq);
					QueryPerformanceCounter(&start);
					wynikiC = watek->noweWatkiC(iloscWatkow, vecDane.size(), vecDane);
					QueryPerformanceCounter(&stop);
					start1 = start.QuadPart;	//Represents a 64 - bit signed integer.
					stop1 = stop.QuadPart;
					freq1 = freq.QuadPart;
					czas = (((stop1)-(start1)) * pow(10,3)) / freq1;
					txtWynik = "Czas sortowania - Dll C: " + std::to_string(czas) + " milisekund";
					tekst = s2ws(txtWynik);
					SetWindowText(hCzas, (LPCWSTR)tekst.c_str());
					txtWynik = "";
					tekst = s2ws("");
					for (int i = 0; i < wynikiC.size(); i++) {
						for (int j = 0; j < wynikiC[i].size(); j++) {
							for (int k = 0; k < wynikiC[i][j].size(); k++) {
								tmp += (to_string((int)wynikiC[i][j][k]) + " ");
							}
							txtWynik += (tmp + "\r\n");
							tmp = "";
						}
					}
					tekst = s2ws(txtWynik);
					SetWindowText(hWynik, (LPCWSTR)tekst.c_str()); //wyswietlenie wyniku
					dane->zapiszDane(wynikiC, czas, iloscWatkow, "wynikiC.txt");
				}
			}
			break;

		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}
//konwersja string do wstring aby wyswietlac
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
