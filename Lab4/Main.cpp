#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <stdarg.h>

using namespace std;

int dGet(string dice)
{
	int result = 0;
	int Throws = 0;
	int dType = 0;
	int dMod = 0;
	bool isPl = false;
	bool isM = false;

	string str = "";
	for (auto ch : dice)
	{
		str += ch;

		if (ch == 'd')
		{
			Throws = stoi(str);
			str = "";
		}
		else if (ch == '+')
		{
			isPl = true;
			dType = stoi(str);
			str = "";
		}
		else if (ch == '-')
		{
			isM = true;
			dType = stoi(str);
			str = "";
		}
	}

	if (isPl) dMod += stoi(str);
	else if (isM) dMod -= stoi(str);
	else dType = stoi(str);

	for (int i = 0; i < Throws; i++) result += rand() % dType + 1;
	result += dMod;

	return result;
}

vector<int> dThrow(int dAmount...)
{
	vector<int> results;

	va_list dices;
	char* dice;

	va_start(dices, dAmount);
	for (int i = 0; i < dAmount; i++)
	{
		dice = va_arg(dices, char*);
		results.push_back(dGet(dice));
	}
	va_end(dices);

	return results;
}
int main()
{

	srand(time(NULL));

	int D1d6[6] = {};
	int D2d6[12] = {};
	int D3d6[18] = {};
	int D1d10[10] = {};
	int D2d10[20] = {};
	int D3d10[30] = {};

	for (int i = 0; i < 100000; i++)
	{
		cout << i + 1 << " throw\n";
		D1d6[dThrow(1, "1d6").at(0) - 1]++;
		D2d6[dThrow(1, "2d6").at(0) - 1]++;
		D3d6[dThrow(1, "3d6").at(0) - 1]++;
		D1d10[dThrow(1, "1d10").at(0) - 1]++;
		D2d10[dThrow(1, "2d10").at(0) - 1]++;
		D3d10[dThrow(1, "3d10").at(0) - 1]++;
	}
	ofstream os("stats.txt");
	for (int i = 0; i < 6; i++) os << D1d6[i] << "\t";
	os << "\n";
	for (int i = 0; i < 12; i++) os << D2d6[i] << "\t";
	os << "\n";
	for (int i = 0; i < 18; i++) os << D3d6[i] << "\t";
	os << "\n";
	for (int i = 0; i < 10; i++) os << D1d10[i] << "\t";
	os << "\n";
	for (int i = 0; i < 20; i++) os << D2d10[i] << "\t";
	os << "\n";
	for (int i = 0; i < 30; i++) os << D3d10[i] << "\t";
	os << "\n";
	os.close();
}