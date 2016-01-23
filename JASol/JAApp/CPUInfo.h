#ifndef CPUINFO_H
#define CPUINFO_H

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "user32.lib")

using namespace std;

class CPUInfo {

private:
	SYSTEM_INFO siSysInfo;

public:
	CPUInfo();
	int pobierzIloscWatkowZProcesora();
};

#endif /* INTERFEJS_H */