#pragma once
#include <iostream>
#include <conio.h>
#include "checkings.h"


bool checkAuthorization(int min, int max, string data, bool consider_digits, bool consider_special_signs) {
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
