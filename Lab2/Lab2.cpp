#include <iostream>
#include "DArray.h"
using namespace std;

class A {
	public:
		A() { ptr = new int[100]; }
		~A() { delete[] ptr; };
	private:
		int* ptr;

	};
	
int main()
{
	A* a = new A();
	a -> ~A();
	
}