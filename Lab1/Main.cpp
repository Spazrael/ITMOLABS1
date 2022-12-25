#include <string>
#include <random>
#include <iostream>
#include <fstream>
#include <locale.h>
#include <utility>
#include <stdexcept>


constexpr int kWheatConsume = 20;
constexpr int kMaxYears = 10;
constexpr char kSaveFileName[] = "save.dat";
constexpr float kLoseCondition = 0.45f;
constexpr int kStartPopulation = 100; 
constexpr int kStartArea = 1000;
constexpr int kStartWheat = 2800;
constexpr float kRatDestructionMax = 0.07f;
constexpr float kSeedsPerSowedAcre = 0.5f;
constexpr int kPlagueProbNum = 3;
constexpr int kAcresByPerson = 10;

constexpr int kAcreDistL = 17;
constexpr int kAcreDistU = 26;
constexpr int kWheatPerAcreDistL = 1;
constexpr int kWheatPerAcreDistU = 6;
constexpr int kPlagueDistL = 1;
constexpr int kPlagueDistU = 20;

int year;
int population;
int wheat;
int area;
int diedLastRound;
int arrived;
bool plagueLastRound;
int wheatCollected;
int wheatPerAcre;
int wheatRatsAte;
int acrePrice;
int sowedArea;
int died;
int eatingBudget;

void new_game();
void loadg();
void saveg();
bool save_exists();
void turn(std::default_random_engine rndEngine_);
void currentTurn();
void player_turn();
int inputCheck();
void game_results();

int main()
{
    setlocale(LC_ALL, "Russian");

    std::random_device rndDevice;
    std::default_random_engine rndEngine(rndDevice());
    std::uniform_int_distribution<int> acreDist(kAcreDistL, kAcreDistU);
    std::uniform_int_distribution<int> wheatPerAcreDist(kWheatPerAcreDistL, kWheatPerAcreDistU);
    std::uniform_int_distribution<int> plagueDist(kPlagueDistL, kPlagueDistU);

    if (save_exists())
    {
        std::cout << "���������� ����������� ����. ���������� ��? (y/n) ";
        if (std::cin.get() == 'y')
        {
            loadg();
            currentTurn();
            player_turn();
        }
        else
        {
            acrePrice = acreDist(rndEngine);
            new_game();
            player_turn();
        }
    }
    else
    {
        acrePrice = acreDist(rndEngine);
        new_game();
        player_turn();
    }

    bool successFlag = true;
    bool exitFlag = false;

    while (year < kMaxYears)
    {
        year++;
        wheatPerAcre = wheatPerAcreDist(rndEngine);
        plagueLastRound = (plagueDist(rndEngine) > kPlagueProbNum ? false : true);
        int populationBackup = population;
        turn(rndEngine);

        if (1.0f * diedLastRound / populationBackup > kLoseCondition || population <= 0)
        {
            successFlag = false;
            break;
        }
        acrePrice = acreDist(rndEngine);
        currentTurn();
        saveg();
        std::cout << "���� ���������. ������ ���������? (y/n) ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (std::cin.get() == 'n')
        {
            exitFlag = true;
            break;
        }
        player_turn();
    }

    if (!exitFlag)
    {
        if (successFlag) game_results();
        else std::cout << "���� ��������. ��-�� ����� ���������������� � ����������, ����� ������� ����, � ������ ��� �� ������. ������ �� ��������� ������� ������ ������������� � ��������.";
    }
}

void new_game()
{
    year = 0;
    population = kStartPopulation;
    wheat = kStartWheat;
    area = kStartArea;
    diedLastRound = 0;
    arrived = 0;
    plagueLastRound = false;
    wheatCollected = 0;
    wheatPerAcre = 0;
    wheatRatsAte = 0;
    sowedArea = 0;
    died = 0;
    eatingBudget = 0;

    std::cout << "��� ����������, �������� �������� ���� � ��������� ��� �� ������ ������ ����������� ���������" << std::endl;
    std::cout << "\t��������� ������ ������ ���������� " << population << " �������;" << std::endl <<
        "\t������ � ��� " << wheat << " ������ ������� � �������;" << std::endl <<
        "\t����� ������ �������� " << area << " �����;" << std::endl <<
        "\t1 ��� ����� ����� ������ " << acrePrice << " ������." << std::endl;
}

void loadg()
{
    std::fstream f;
    f.open(kSaveFileName, std::fstream::in);
    std::string s;
    std::getline(f, s);
    year = std::stoi(s);
    std::getline(f, s);
    population = std::stoi(s);
    std::getline(f, s);
    wheat = std::stoi(s);
    std::getline(f, s);
    area = std::stoi(s);
    std::getline(f, s);
    diedLastRound = std::stoi(s);
    std::getline(f, s);
    arrived = std::stoi(s);
    std::getline(f, s);
    plagueLastRound = std::stoi(s);
    std::getline(f, s);
    wheatCollected = std::stoi(s);
    std::getline(f, s);
    wheatPerAcre = std::stoi(s);
    std::getline(f, s);
    wheatRatsAte = std::stoi(s);
    std::getline(f, s);
    acrePrice = std::stoi(s);
    std::getline(f, s);
    sowedArea = std::stoi(s);
    std::getline(f, s);
    died = std::stoi(s);
    std::getline(f, s);
    eatingBudget = std::stoi(s);
    f.close();
}

void saveg()
{
    std::string s = "";
    s.append(std::to_string(year));
    s.append("\n");
    s.append(std::to_string(population));
    s.append("\n");
    s.append(std::to_string(wheat));
    s.append("\n");
    s.append(std::to_string(area));
    s.append("\n");
    s.append(std::to_string(diedLastRound));
    s.append("\n");
    s.append(std::to_string(arrived));
    s.append("\n");
    s.append(std::to_string(plagueLastRound));
    s.append("\n");
    s.append(std::to_string(wheatCollected));
    s.append("\n");
    s.append(std::to_string(wheatPerAcre));
    s.append("\n");
    s.append(std::to_string(wheatRatsAte));
    s.append("\n");
    s.append(std::to_string(acrePrice));
    s.append("\n");
    s.append(std::to_string(sowedArea));
    s.append("\n");
    s.append(std::to_string(died));
    s.append("\n");
    s.append(std::to_string(eatingBudget));
    s.append("\n");
    std::fstream f;
    f.open(kSaveFileName, std::fstream::out);
    f.write(s.c_str(), s.size());
    f.close();
}

bool save_exists()
{
    std::ifstream sFile(kSaveFileName);
    return sFile.good();
}

void player_turn()
{
    std::cout << "��� ���������, ����������?" << std::endl;
    int buyInput = 0;
    int sellInput = 0;
    int eatInput = 0;
    int sowInput = 0;
    while (true)
    {
        std::cout << "������� ����� ����� ����������� ������? ";
        buyInput = inputCheck();
        std::cout << "������� ����� ����� ����������� �������? ";
        sellInput = inputCheck();
        std::cout << "������� ������� ������� ����������� ������? ";
        eatInput = inputCheck();
        std::cout << "������� ����� ����� ����������� �������? ";
        sowInput = inputCheck();


        if (wheat - (buyInput - sellInput) * acrePrice - eatInput - ceil(sowInput * kSeedsPerSowedAcre) > 0 && sowInput <= kAcresByPerson * population && area >= sowInput) break;
        std::cout << "�, ����������, ������ ���! � ��� ������ " << population << " �������, " << wheat << " ������� ������� � " << area << " ����� �����!" << std::endl;
    }
    area += buyInput - sellInput;
    wheat -= (buyInput - sellInput) * acrePrice + ceil(sowInput * kSeedsPerSowedAcre);
    sowedArea = sowInput;
    eatingBudget = eatInput;
}

void turn(std::default_random_engine rndEngine_)
{
    wheatCollected = wheatPerAcre * sowedArea;
    wheat += wheatCollected;
    wheat -= eatingBudget;
    std::uniform_int_distribution<int> ratDist(0, round(kRatDestructionMax * wheat));
    wheatRatsAte = ratDist(rndEngine_);
    if (wheatRatsAte > wheat) wheatRatsAte = wheat;
    wheat -= wheatRatsAte;
    if (eatingBudget >= population * kWheatConsume) diedLastRound = 0;
    else diedLastRound = population - eatingBudget / kWheatConsume;
    population -= diedLastRound;
    arrived = diedLastRound / 2 + (5 - wheatPerAcre) * wheat / 600 + 1;
    if (arrived < 0) arrived = 0;
    population += arrived;
    if (plagueLastRound) population = population / 2;
}

void game_results()
{
    float p = 1.0f * died / kMaxYears;
    int l = area / population;


    if (p > 0.33f && l < 7)
        std::cout << "��-�� ����� ���������������� � ����������, ����� ������� ����, � ������ ��� �� ������.������ �� ��������� ������� ������ ������������� � ��������" << std::endl;
    else if (p > 0.10f && l < 9)
        std::cout << "�� ������� �������� �����, ������� ������ � ����� ��������.����� �������� � �����������, � ����� ������ �� ������ ������ ��� ����������" << std::endl;
    else if (p > 0.03f && l < 10)
        std::cout << "�� ���������� ������ �������, � ���, �������, ���� ���������������, �� ������ ������ �� ������� ��� �� ����� ������ �����" << std::endl;
    else
        std::cout << "����������! ���� �������, �������� � ���������� ������ �� ���������� �� �����." << std::endl;
}

int inputCheck()
{
    std::string input = "";
    int output = INT32_MIN;
    do
    {
        std::cin >> input;
        try
        {
            output = std::stoi(input);
        }
        catch (std::invalid_argument const& ex)
        {
            std::cout << "������� �����." << std::endl;
        }
        catch (std::out_of_range const& ex)
        {
            std::cout << "������� ����� ����������� ���������." << std::endl;
        }
        if (output < 0)
            std::cout << "������� ��������������� �����." << std::endl;
    } while (output < 0);
    return output;
}

void currentTurn()
{
    std::cout << "��� ����������, �������� �������� ����" << std::endl <<
        "\t� ���� " << year << " ������ ����������� ���������" << std::endl;
    if (diedLastRound > 0)
    {
        std::cout << "\t" << diedLastRound << " ������� ������ � ������";
        if (arrived > 0) std::cout << ", � " << arrived << " ������� ������� � ��� ������� �����";
    }
    else if (arrived > 0) std::cout << "\t" << arrived << " ������� ������� � ��� ������� �����";
    if (diedLastRound > 0 || arrived > 0) std::cout << ";" << std::endl;
    if (plagueLastRound) std::cout << "\t���� ���������� �������� ���������;" << std::endl;
    std::cout << "\t��������� ������ ������ ���������� " << population << " �������;" << std::endl <<
        "\t�� ������� " << wheatCollected << " ������� �������, �� " << wheatPerAcre << " ������ � ����;" << std::endl <<
        "\t����� ��������� " << wheatRatsAte << " ������� �������, ������� " << wheat << " ������ � �������;" << std::endl <<
        "\t����� ������ �������� " << area << " �����;" << std::endl <<
        "\t1 ��� ����� ����� ������ " << acrePrice << " ������." << std::endl;
}