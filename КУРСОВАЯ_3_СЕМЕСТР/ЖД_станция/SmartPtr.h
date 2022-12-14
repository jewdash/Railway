#pragma once
#include <iostream>

using namespace std;

template<class T>
struct Status {
	T* ptr;
	int counter;
};

template<class T>
class SmartPointer
{
	Status<T>* smartPtr;
public:
	SmartPointer();

	SmartPointer(T* ptr);

	~SmartPointer();

	SmartPointer(const SmartPointer& obj);

	void operator=(const SmartPointer& obj);

	T* operator->() const;

	void showCounter();
};
