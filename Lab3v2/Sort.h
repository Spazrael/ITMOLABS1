#pragma once
#include <iostream>
using namespace std;

constexpr int algChange = 15;

template<typename T> void Swap(T* a, T* b) {
    T tmp(std::move(*a));
    *a = move(*b);
    *b = move(tmp);
}

template<typename T, typename Compare> T* choosePivot(T* first, T* last, Compare comp) {

    T* middle = first + (last - first) / 2;
    T pivot;
    last--;
    if (comp(*middle, *first) && comp(*first, *last) || comp(*last, *first) && comp(*first, *middle)) { pivot = *first; }
    else if (comp(*first, *middle) && comp(*middle, *last) || comp(*last, *middle) && comp(*middle, *first)) { pivot = *middle; }
    else pivot = *last;
    last++;
    T* p = first, * q = last - 1;
    while (p < q) {
        while (comp(*p, pivot)) { p++; }
        while (comp(pivot, *q)) { q--; }
        if (p < q) {
            if (*q == *p) { p++; }
            else { Swap(p, q); }
        }
    }

    return q;
}

template<typename T, typename Compare> void insertionSort(T* first, T* last, Compare comp) {
    for (T* p = first + 1; p < last; p++) {
        T* q = p - 1;
        T tmp = move(*p);
        while (q >= first && comp(tmp, *q)) {
            *(q + 1) =move(*q);
            q--;
        }
        *(q + 1) = move(tmp);
    }
}


template<typename T, typename Compare> void quickSort(T* first, T* last, Compare comp) {
    while (first < last) {
        T* pivot = choosePivot(first, last, comp);
        if (pivot - first < last - pivot + 1) {
            quickSort(first, pivot, comp);
            first = pivot + 1;
        }
        else {
            quickSort(pivot + 1, last, comp);
            last = pivot;
        }
    }
}


template<typename T, typename Compare> void sort(T* first, T* last, Compare comp) {
    while (last - first > algChange) {
        T* pivot = choosePivot(first, last, comp);
        if (pivot - first < last - pivot + 1) {
            sort(first, pivot, comp);
            first = pivot + 1;
        }
        else {
            sort(pivot + 1, last, comp);
            last = pivot;
        }
    }
    insertionSort(first, last, comp);
}