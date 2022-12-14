#pragma once
#include <iostream>
#include <conio.h>
#include <random>
#include <time.h>
#include <ctime>
#include "ticket.h"
#include "checkings.h"

bool additional_funcs::checkAuthorization(int min, int max, string data, bool consider_digits, bool consider_special_signs) {
	if (data.size() > max || data.size() < min) return false;
	int ctr = 0;
	for (int i = 0; i < data.size(); i++) {
		if ((data[i] >= (char)65 && data[i] <= (char)90) || (data[i] >= (char)97 && data[i] <= (char)122)) ctr++;
	}
	if (!ctr) return false;
	for (int i = 0; i < data.size(); i++) {
		if (data[i] >= (char)32 && data[i] <= (char)47) return false;
	}
	if (consider_digits) {
		int count = 0;
		for (int i = 0; i < data.size(); i++)
			if (data[i] >= (char)48 && data[i] <= (char)57) count++;
		if (!count) return false;
	}
	if (consider_special_signs) {
		int count = 0;
		for (int i = 0; i < data.size(); i++)
			if (data[i] == '_') count++;
		if (!count) return false;
	}

	return true;
}

void additional_funcs::generateID(int id) {
	id = (1000 + rand() % 10000) - 1000;
}

bool additional_funcs::checkDateTime(DateTime dt) {
	if (dt.getY() < 1970 || dt.getY() > 2100) return false;
	if (dt.getMth() < 1 || dt.getMth() > 12) return false;
	switch (dt.getMth()) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		if (dt.getD() < 1 || dt.getD() > 31) return false;
	case 4: case 6: case 9: case 11:
		if (dt.getD() < 1 || dt.getD() > 30) return false;
	case 2: {
		if (dt.getMth() % 4 == 0) {
			if (dt.getD() < 1 || dt.getD() > 29) return false;
		}
		else {
			if (dt.getD() < 1 || dt.getD() > 28) return false;
		}
	}
	}
	if (dt.getH() < 0 || dt.getH() > 23) return false;
	if (dt.getMts() < 0 || dt.getMts() > 59) return false;
	return true;
}

string additional_funcs::getUppercaseString(string str) {
	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= (char)97 && str[i] <= (char)122) {
			str[i] -= (char)32;
		}
		if (str[i] >= (char)224 && str[i] <= (char)255) {
			str[i] -= (char)32;
		}
	}

	return str;
}

template<class T>
void additional_funcs::swap(T& elem_1, T& elem_2) {
	T temporary;
	temporary = elem_1;
	elem_1 = elem_2;
	elem_2 = temporary;
}