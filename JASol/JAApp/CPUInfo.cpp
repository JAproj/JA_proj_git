#include "stdafx.h"
#include"CPUInfo.h"
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "user32.lib")

CPUInfo::CPUInfo() {}

int CPUInfo::pobierzIloscWatkowZProcesora() {

	//kopiowanie info o procesorze to struktury SYSTEM_INFO
	GetSystemInfo(&siSysInfo);
	return siSysInfo.dwNumberOfProcessors;
}