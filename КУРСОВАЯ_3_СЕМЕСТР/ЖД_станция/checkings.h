#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include "ticket.h"
//extern HANDLE hStdOut;
using std::cout;
using std::cin;
using std::endl;
using std::string;

bool checkAuthorization(int, int, string, bool, bool);
void generateID(int);
bool checkDateTime(DateTime);
string getUppercaseString(string);
//DateTime getCurrentDate();
