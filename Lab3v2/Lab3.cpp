#include <iostream>
#include <fstream>
#include "Sort.h"
#include <Windows.h>
using namespace std;

constexpr int cyclesNum = 10000;
constexpr int maxLen = 20;
int main()
{
    LARGE_INTEGER sTime, eTime;
    LARGE_INTEGER frequency;
    int a[maxLen];
    QueryPerformanceFrequency(&frequency);
    double bFrequency = double(frequency.QuadPart) / 1000;

    ofstream file1("quickSort.txt", ios_base::out | ios_base::trunc);

    for (int arrLen = 1; arrLen < maxLen; arrLen++) {
        cout.width(2);
        cout << arrLen << " ";
        QueryPerformanceCounter(&sTime);
        for (int cycle = 0; cycle < cyclesNum; cycle++) {
            for (int i = 0; i < arrLen; i++) { a[i] = arrLen - i; }
            quickSort(a, a + arrLen, [](int a, int b) { return a < b; });
        }
        QueryPerformanceCounter(&eTime);
        file1 << (eTime.QuadPart - sTime.QuadPart) / bFrequency << endl;
        cout << (eTime.QuadPart - sTime.QuadPart) / bFrequency << endl;
    }
    file1.close();

    file1.open("insertionSort.txt", ios_base::out | ios_base::trunc);

    for (int arrLen = 1; arrLen < maxLen; arrLen++) {
        cout.width(2);
        cout << arrLen << " ";
        QueryPerformanceCounter(&sTime);
        for (int cycle = 0; cycle < cyclesNum; cycle++) {
            for (int i = 0; i < arrLen; i++) { a[i] = arrLen - i; }
            insertionSort(a, a + arrLen, [](int a, int b) { return a < b; });
        }
        QueryPerformanceCounter(&eTime);
        file1 << (eTime.QuadPart - sTime.QuadPart) / bFrequency << endl;
        cout << (eTime.QuadPart - sTime.QuadPart) / bFrequency << endl;
    }
    file1.close();

    file1.open("hybridSort.txt", ios_base::out | ios_base::trunc);

    for (int arrLen = 1; arrLen < maxLen; arrLen++) {
        cout.width(2);
        cout << arrLen << " ";
        QueryPerformanceCounter(&sTime);
        for (int cycle = 0; cycle < cyclesNum; cycle++) {
            for (int i = 0; i < arrLen; i++) { a[i] = arrLen - i; }
            sort(a, a + arrLen, [](int a, int b) { return a < b; });
        }
        QueryPerformanceCounter(&eTime);
        file1 << (eTime.QuadPart - sTime.QuadPart) / bFrequency << endl;
        cout << (eTime.QuadPart - sTime.QuadPart) / bFrequency << endl;
    }
    file1.close();

}