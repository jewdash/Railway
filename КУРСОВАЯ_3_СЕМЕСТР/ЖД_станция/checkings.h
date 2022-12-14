#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include "ticket.h"
#include <ctime>
//extern HANDLE hStdOut;
using std::cout;
using std::cin;
using std::endl;
using std::string;

namespace additional_funcs {
	bool checkAuthorization(int, int, string, bool, bool);
	void generateID(int);
	bool checkDateTime(DateTime);
	string getUppercaseString(string);

	template<class T>
	void swap(T&, T&);
}
//DateTime getCurrentDate();
