#include "pch.h"
#include "U:/VSPROJECTS/Lab2/DArray.h"

#pragma region DefaultType
TEST(DAConstructorTestInt, TestDefaultConstructor)
{
	DArray<int> array;
	ASSERT_EQ(array.size(), 0);
	ASSERT_EQ(array.capacity(), 8);
}

TEST(DAConstructorTestInt, TestSizeConstructor)
{
	DArray<int> array(10);
	ASSERT_EQ(array.size(), 0);
	ASSERT_EQ(array.capacity(), 10);
}

TEST(DAConstructorTestInt, TestCopyConstructor)
{
	DArray<int> arrayA(10);
	for (int i = 0; i < arrayA.size(); ++i)
		arrayA.insert(i);

	DArray<int> arrayB{ arrayA };

	ASSERT_EQ(arrayA.size(), arrayB.size());
	ASSERT_EQ(arrayA.capacity(), arrayB.capacity());

	for (int i = 0; i < arrayA.size(); ++i) 
		ASSERT_EQ(arrayA[i], arrayB[i]);
}

TEST(DAConstructorTestInt, TestMoveConstructor)
{
	DArray<int> arrayA(10);
	for (int i = 0; i < arrayA.size(); ++i)
		arrayA.insert(i);

	int arrayACapacity = arrayA.capacity();
	int arrayASize = arrayA.size();

	DArray<int> arrayB = std::move(arrayA);

	ASSERT_EQ(arrayACapacity, arrayB.capacity());
	ASSERT_EQ(arrayASize, arrayB.size());
	for (int i = 0; i < arrayB.size(); ++i)
		ASSERT_EQ(arrayB[i], i);
}

TEST(DAConstructorTestInt, ExpansionTest)
{
	DArray<int> array;
	ASSERT_EQ(array.capacity(), 8);

	for (int i = 0; i < 9; ++i)
		array.insert(i);
	ASSERT_EQ(array.capacity(), 16);

	for (int i = 0; i < 9; ++i)
		array.insert(i);
	ASSERT_EQ(array.capacity(), 32);
}

TEST(DAConstructorTestInt, InsertTest)
{
	DArray<int> array;
	for (int i = 0; i < 5; ++i)
		array.insert(i);

	ASSERT_EQ(array.insert(3, 100), 3);
	ASSERT_EQ(array[3], 100);

	ASSERT_EQ(array.insert(0, 101), 0);
	ASSERT_EQ(array[0], 101);
}

TEST(DAConstructorTestInt, RemoveTest)
{ 
	DArray<int> array;
	for (int i = 0; i < 5; ++i)
		array.insert(i);

	array.remove(3);
	ASSERT_EQ(array[3], 4);

	array.remove(0);
	ASSERT_EQ(array[0], 1);
}

#pragma endregion DefaultType

#pragma region std::string
TEST(DAConstructorTestString, TestDefaultConstructor)
{
	DArray<std::string> array;
	ASSERT_EQ(array.size(), 0);
	ASSERT_EQ(array.capacity(), 8);
}

TEST(DAConstructorTestString, TestSizeConstructor)
{
	DArray<std::string> array(10);
	ASSERT_EQ(array.size(), 0);
	ASSERT_EQ(array.capacity(), 10);
}

TEST(DAConstructorTestString, TestCopyConstructor)
{
	DArray<std::string> arrayA(10);
	for (int i = 0; i < arrayA.size(); ++i)
		arrayA.insert(std::to_string(i));

	DArray<std::string> arrayB{ arrayA };

	ASSERT_EQ(arrayA.size(), arrayB.size());
	ASSERT_EQ(arrayA.capacity(), arrayB.capacity());

	for (int i = 0; i < arrayA.size(); ++i)
		ASSERT_EQ(arrayA[i], arrayB[i]);
}

TEST(DAConstructorTestString, TestMoveConstructor)
{
	DArray<std::string> arrayA(10);
	for (int i = 0; i < arrayA.size(); ++i)
		arrayA.insert(std::to_string(i));

	int arrayACapacity = arrayA.capacity();
	int arrayASize = arrayA.size();

	DArray<std::string> arrayB = std::move(arrayA);

	ASSERT_EQ(arrayACapacity, arrayB.capacity());
	ASSERT_EQ(arrayASize, arrayB.size());
	for (int i = 0; i < arrayB.size(); ++i)
		ASSERT_EQ(arrayB[i], std::to_string(i));
}

TEST(DAConstructorTestString, ExpansionTest)
{
	DArray<std::string> array;
	ASSERT_EQ(array.capacity(), 8);

	for (int i = 0; i < 9; ++i)
		array.insert(std::to_string(i));
	ASSERT_EQ(array.capacity(), 16);

	for (int i = 0; i < 9; ++i)
		array.insert(std::to_string(i));
	ASSERT_EQ(array.capacity(), 32);
}

TEST(DAConstructorTestString, InsertTest)
{
	DArray<std::string> array;
	for (int i = 0; i < 5; ++i)
		array.insert(std::to_string(i));

	ASSERT_EQ(array.insert(3, "100"), 3);
	ASSERT_EQ(array[3], "100");

	ASSERT_EQ(array.insert(0, "101"), 0);
	ASSERT_EQ(array[0], "101");
}

TEST(DAConstructorTestString, RemoveTest)
{
	DArray<std::string> array;
	for (int i = 0; i < 5; ++i)
		array.insert(std::to_string(i));

	array.remove(3);
	ASSERT_EQ(array[3], "4");

	array.remove(0);
	ASSERT_EQ(array[0], "1");
	
	


}

#pragma endregion std::string

#pragma region Iterator
TEST(DAIterator, ForwardIterator)
{
	int count = 0;
	DArray<int> array(10);
	for (int i = 0; i < array.size(); ++i)
		array.insert(i);

	for (auto it = array.iterator(); it.hasNext(); it.next())
	{
		EXPECT_EQ(it.get(), count);
		++count;
	}
}

TEST(DAIterator, ReversedIterator)
{
	int count = 9;
	DArray<int> array(10);
	for (int i = 0; i < array.size(); ++i)
		array.insert(i);

	for (auto it = array.iterator(); it.hasNext(); it.next())
	{
		EXPECT_EQ(it.get(), count);
		--count;
	}
}
#pragma endregion Iterator