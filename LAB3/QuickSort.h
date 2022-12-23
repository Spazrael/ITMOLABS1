#pragma once


constexpr int valueToUseInsertionSort = 22;
// �������� ���������� ���������
// �� ������ �������� �� �������� VALUE ������ ������� �������� �������� ������������������
// ����� �� ��������� ���������� ����� �� �������� �������� ������� ������������������ ������ �� ��� ���
// ���� �� ������ � ���� ������������������ ��������� ������� VALUE �� ������� ��������������� ������� ������������������
template<typename T, typename Compare>
void InsertionSort(T* first, T* last, Compare comp) {
	if (first == last) { return; }
	T value;
	T* j;
	for (T* i = first + 1; i <= last; i++) {
		value = (*i);
		j = i;
		while (j > first && comp(value, *(j - 1))) {
			(*j) = std::move(*(j - 1));
			j--;
		}
		(*j) = std::move(value);
	}
}

// ������� ���������� ���������� ��������
template<typename T, typename Compare>
T FindMedian(T& a, T& b, T& c, Compare compare) {
	if ((compare(a, b) && compare(c, a)) || ((compare(a, c) && compare(b, a)))) { return a; }
	else if ((compare(b, a) && compare(c, b)) || (compare(b, c) && compare(a, b))) { return b; }
	else { return c; }
}

// �������� ������� ����������
// ������ ���������: ������ ������� leftPtr = first, ������� rightPtr = last, � �������� ������� ������� pivot �� �������
// ����� �������� ������� leftPtr � rightRtr ���� � ����� �� ��� ���, ���� *leftPtr > pivot, � *rightPtr < pivot
// ��� ������ ����� �������� > *leftPtr � < *rightPtr ������ �� �������
// (�� ���� ������� �������� �� ��������� �����, � ��������� �������� �����)
// ��������� ��������� �� ��� ���, ���� �� ���������� leftPtr >= rightPtr
// (�� ���� ���� ��� ������� �� �����������)
// ����� ���������� ��������� �������� ������� ����������
template<typename T, typename Compare>
void QuickSort(T* first, T* last, Compare compare, bool useInsertionSort = true) {
    while (first < last) {
        if (useInsertionSort) {
            if ((last - first) < valueToUseInsertionSort) InsertionSort(first, last, compare);
        }
        T pivot = FindMedian(*first, *last, *(first + ((last - first) / 2)), compare);
        T* left = first;
        T* right = last;
        while (true) {
            while (compare(*left, pivot)) left++;
            while (compare(pivot, *right)) right--;
            if (left >= right) break;
            std::swap(*left, *right);
            left++;
            right--;
        }
        if (last - right > right - first) {
            QuickSort(first, right, compare);
            first = right + 1;
        }
        else {
            QuickSort(right + 1, last, compare);
            last = right;
        }
    }
}