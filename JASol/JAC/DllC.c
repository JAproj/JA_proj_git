int* MyFuncC(int size, int* table)
{
	int i, j, temp;
//	int size = sizeof table; zwraca rozmiar wskaünika- tu4
	for (i = 0; i<size - 1; i++)
	{
		for (j = 0; j<size - 1 - i; j++)
		{
			if (table[j] > table[j + 1])
			{
				temp = table[j + 1];
				table[j + 1] = table[j];
				table[j] = temp;
			}
		}
	}
	return table;
}