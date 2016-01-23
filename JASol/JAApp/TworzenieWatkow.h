#ifndef TWORZENIEWATKOW_H
#define TWORZENIEWATKOW_H
#include "stdafx.h"
#include "ObslugaDll.h"  
#include <future>

class TworzenieWatkow
{
private:
	vector<vector<int>> wynik;

public:
	TworzenieWatkow();

	void watekAsm(vector<vector<int>>, ObslugaDll*, promise<vector<vector<int>>>&);
	void watekC(vector<vector<int>>, ObslugaDll*, promise<vector<vector<int>>>&);

};

#endif /* TWORZENIEWATKOW_H */