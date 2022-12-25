#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <random>
#include <string>

int GetDice(std::string dice)
{
	int result = 0;
	int Throws = 0;
	int dType = 0;
	int dMod = 0;
	bool isPlus = false;
	bool isMinus = false;

	std::string str = "";
	for (auto ch : dice)
	{
		str += ch;

		if (ch == 'd')
		{
			Throws = std::stoi(str);
			str = "";
		}
		else if (ch == '+')
		{
			isPlus = true;
			dType = std::stoi(str);
			str = "";
		}
		else if (ch == '-')
		{
			isMinus = true;
			dType = std::stoi(str);
			str = "";
		}
	}

	if (isPlus) dMod += std::stoi(str);
	else if (isMinus) dMod -= std::stoi(str);
	else dType = std::stoi(str);

	for (int i = 0; i < Throws; i++) result += std::rand() % dType + 1;
	result += dMod;

	return result;
}

std::vector<int> ThrowDice(int dAmount...)
{
	std::vector<int> results;

	va_list dices;
	char* dice;

	va_start(dices, dAmount);
	for (int i = 0; i < dAmount; i++)
	{
		dice = va_arg(dices, char*);
		results.push_back(GetDice(dice));
	}
	va_end(dices);

	return results;
}
int main()
{

    std::srand(time(NULL));

    int D1d6[6] = {};
    int D2d6[12] = {};
    int D3d6[18] = {};
    int D1d10[10] = {};
    int D2d10[20] = {};
    int D3d10[30] = {};

    for (int i = 0; i < 100; i++)
    {
        std::cout << i + 1 << " throw\n";
        D1d6[ThrowDice(1, "1d6").at(0) - 1]++;
        D2d6[ThrowDice(1, "2d6").at(0) - 1]++;
        D3d6[ThrowDice(1, "3d6").at(0) - 1]++;
        D1d10[ThrowDice(1, "1d10").at(0) - 1]++;
        D2d10[ThrowDice(1, "2d10").at(0) - 1]++;
        D3d10[ThrowDice(1, "3d10").at(0) - 1]++;
    }

    std::ofstream os("stats.txt");
    for (int i = 0; i < sizeof(D1d6) / sizeof(*D1d6); i++) os << D1d6[i] << "\t";
    os << "\n";
    for (int i = 0; i < sizeof(D2d6) / sizeof(*D2d6); i++) os << D2d6[i] << "\t";
    os << "\n";
    for (int i = 0; i < sizeof(D3d6) / sizeof(*D3d6); i++) os << D3d6[i] << "\t";
    os << "\n";
    for (int i = 0; i < sizeof(D1d10) / sizeof(*D1d10); i++) os << D1d10[i] << "\t";
    os << "\n";
    for (int i = 0; i < sizeof(D2d10) / sizeof(*D2d10); i++) os << D2d10[i] << "\t";
    os << "\n";
    for (int i = 0; i < sizeof(D3d10) / sizeof(*D3d10); i++) os << D3d10[i] << "\t";
    os << "\n"; 
    os.close();
}