#include "pch.h"
#include "U:/VSPROJECTS/Lab3v2/Sort.h"

TEST(QuickSortTest, quickSortDefault) {
	constexpr int n = 10;
	int a[n];
	for (int i = 0; i < n; i++) { a[i] = n - i; }
	quickSort(a, a + n, [](int a, int b) { return a < b; });
	for (int i = 0; i < n; i++) { ASSERT_EQ(i + 1, a[i]); }
}

TEST(QuickSortTest, quickSortOne) {
	constexpr int n = 1;
	int a[n];
	for (int i = 0; i < n; i++) { a[i] = n - i; }
	quickSort(a, a + n, [](int a, int b) { return a < b; });
	for (int i = 0; i < n; i++) { ASSERT_EQ(i + 1, a[i]); }
}
TEST(QuickSortTest, quickSortThree) {
	constexpr int n = 3;
	int a[n];
	for (int i = 0; i < n; i++) { a[i] = n - i; }
	quickSort(a, a + n, [](int a, int b) { return a < b; });
	for (int i = 0; i < n; i++) { ASSERT_EQ(i + 1, a[i]); }
}
TEST(QuickSortTest, quickSortFifteen) {
	constexpr int n = 15;
	int a[n];
	for (int i = 0; i < n; i++) { a[i] = n - i; }
	quickSort(a, a + n, [](int a, int b) { return a < b; });
	for (int i = 0; i < n; i++) { ASSERT_EQ(i + 1, a[i]); }
}
TEST(QuickSortTest, quickSortThousand) {
	constexpr int n = 1000;
	int a[n];
	for (int i = 0; i < n; i++) { a[i] = n - i; }
	quickSort(a, a + n, [](int a, int b) { return a < b; });
	for (int i = 0; i < n; i++) { ASSERT_EQ(i + 1, a[i]); }
}

TEST(InsertionSortTest, insertionSortDefault) {
	constexpr int n = 10;
	int a[n];
	for (int i = 0; i < n; i++) { a[i] = n - i; }
	insertionSort(a, a + n, [](int a, int b) { return a < b; });
	for (int i = 0; i < n; i++) { ASSERT_EQ(i + 1, a[i]); }
}

TEST(InsertionSortTest, insertionSortOne) {
	constexpr int n = 1;
	int a[n];
	for (int i = 0; i < n; i++) { a[i] = n - i; }
	insertionSort(a, a + n, [](int a, int b) { return a < b; });
	for (int i = 0; i < n; i++) { ASSERT_EQ(i + 1, a[i]); }
}
TEST(InsertionSortTest, insertionSortThree) {
	constexpr int n = 3;
	int a[n];
	for (int i = 0; i < n; i++) { a[i] = n - i; }
	insertionSort(a, a + n, [](int a, int b) { return a < b; });
	for (int i = 0; i < n; i++) { ASSERT_EQ(i + 1, a[i]); }
}
TEST(InsertionSortTest, insertionSortFifteen) {
	constexpr int n = 15;
	int a[n];
	for (int i = 0; i < n; i++) { a[i] = n - i; }
	insertionSort(a, a + n, [](int a, int b) { return a < b; });
	for (int i = 0; i < n; i++) { ASSERT_EQ(i + 1, a[i]); }
}
TEST(InsertionSortTest, insertionSortThousand) {
	constexpr int n = 1000;
	int a[n];
	for (int i = 0; i < n; i++) { a[i] = n - i; }
	insertionSort(a, a + n, [](int a, int b) { return a < b; });
	for (int i = 0; i < n; i++) { ASSERT_EQ(i + 1, a[i]); }
}

TEST(HybridSortTest, hybridSortDefault) {
	constexpr int n = 10;
	int a[n];
	for (int i = 0; i < n; i++) { a[i] = n - i; }
	sort(a, a + n, [](int a, int b) { return a < b; });
	for (int i = 0; i < n; i++) { ASSERT_EQ(i + 1, a[i]); }
}

TEST(HybridSortTest, hybridSortOne) {
	constexpr int n = 1;
	int a[n];
	for (int i = 0; i < n; i++) { a[i] = n - i; }
	sort(a, a + n, [](int a, int b) { return a < b; });
	for (int i = 0; i < n; i++) { ASSERT_EQ(i + 1, a[i]); }
}
TEST(HybridSortTest, hybridSortThree) {
	constexpr int n = 3;
	int a[n];
	for (int i = 0; i < n; i++) { a[i] = n - i; }
	sort(a, a + n, [](int a, int b) { return a < b; });
	for (int i = 0; i < n; i++) { ASSERT_EQ(i + 1, a[i]); }
}
TEST(HybridSortTest, hybridSortFifteen) {
	constexpr int n = 15;
	int a[n];
	for (int i = 0; i < n; i++) { a[i] = n - i; }
	sort(a, a + n, [](int a, int b) { return a < b; });
	for (int i = 0; i < n; i++) { ASSERT_EQ(i + 1, a[i]); }
}
TEST(HybridSortTest, hybridSortThousand) {
	constexpr int n = 1000;
	int a[n];
	for (int i = 0; i < n; i++) { a[i] = n - i; }
	sort(a, a + n, [](int a, int b) { return a < b; });
	for (int i = 0; i < n; i++) { ASSERT_EQ(i + 1, a[i]); }
}