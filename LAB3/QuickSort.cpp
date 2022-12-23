#include <iostream>
#include "QuickSort.h"
#include <chrono>
#include <iomanip>
#include <fstream>
#include <windows.h>

// Функционал для замера времени выполнения функций InsertionSort и QuickSort
double PCFreq = 0.0;
__int64 CounterStart = 0;
void StartCounter() {
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li)) { std::cout << "QueryPerformanceFrequency failed!\n"; }
    PCFreq = double(li.QuadPart / 1000000.0);
    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}
// Вспомогательный функционал для замера времени выполнения функций InsertionSort и QuickSort
struct Performance {
    double insertionSortResult;
    double quickSortResult;
};
template<typename T, typename Compare>
Performance StartTest(int arraySize, Compare compare) {
    srand(time(nullptr));
    T* insertSortArray = new T[arraySize];
    T* quickSortArray = new T[arraySize];
    for (int i = 0; i < arraySize; i++) {
        quickSortArray[i] = i;
        insertSortArray[i] = arraySize - i;
    }
    StartCounter();
    QuickSort(quickSortArray, quickSortArray + arraySize - 1, compare, false);
    double quickSortResult = GetCounter();
    StartCounter();
    InsertionSort(insertSortArray, insertSortArray + arraySize - 1, compare);
    double insertionSortResult = GetCounter();
    delete[] quickSortArray;
    delete[] insertSortArray;
    return { insertionSortResult, quickSortResult };
}
int main()
{
std::fstream fs;
fs.open("./result.txt", std::fstream::out | std::ofstream::trunc);
const int numberOfTests = 10000;
for (int i = 0; i < 30; ++i) {
    double insertSum = 0;
    double quickSum = 0;
    for (int j = 0; j < numberOfTests; ++j) {
        Performance result = StartTest<int>(i, [](int a, int b) { return a < b; });
        insertSum += result.insertionSortResult;
        quickSum += result.quickSortResult;
    }
    fs << i << " " << insertSum / numberOfTests << " " << quickSum / numberOfTests << std::endl;
    std::cout << "Array size: " << i << std::endl;
    std::cout << " InsertionSort time: " << insertSum / numberOfTests << std::endl;
    std::cout << " QuickSort time: " << quickSum / numberOfTests << std::endl;
    if (insertSum / numberOfTests < quickSum / numberOfTests) {
        std::cout << "  FASTER - InsertionSort" << std::endl;
    }
    else {
        std::cout << "  FASTER - QuickSort" << std::endl;
    }
    std::cout << std::endl;
}
fs.close();
return EXIT_SUCCESS;
}