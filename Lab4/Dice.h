#pragma once

#include <string>
#include <random>
#include <stdarg.h>

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