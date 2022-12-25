#pragma once

class TestObject
{
	int* p;
public:
	TestObject(int a) {
		p = new int;
		*p = a;
	}
	TestObject(const TestObject& to) {
		p = new int;
		*p = *(to.p);
	}
	int GetInt() {
		return *p;
	}
	~TestObject() {
		delete p;
	}
};
