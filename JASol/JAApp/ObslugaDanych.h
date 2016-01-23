#ifndef OBSLUGADANYCH_H
#define OBSLUGADANYCH_H
#include <vector>
#include <string>
using namespace std;
class ObslugaDanych
{

private:
	vector<vector<int>> vecDane;
	vector<int> vecDlugoscLiniDanych;

public:
	ObslugaDanych();

	vector<vector<int>> pobierzDane();
	void zapiszDane(vector<vector<vector<int>>>, unsigned __int64, int, string);
};

#endif /* OBSLUGADANYCH_H */

