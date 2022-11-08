#pragma once
#include <iostream>
#include <conio.h>
#include "checkings.h"
#include "console_settings.h"


bool checkAuthorization(int min, int max, string data, bool consider_digits, bool consider_special_signs) {
	if (data.size() > max || data.size() < min) return false;
	int ctr = 0;
	for (int i = 0; i < data.size(); i++) {
		if ((data[i] >= 65 && data[i] <= 90) || (data[i] >= 97 && data[i] <= 122)) ctr++;
	}
	if (!ctr) return false;
	for (int i = 0; i < data.size(); i++) {
		if (data[i] >= 32 && data[i] <= 47) return false;
	}
	if (consider_digits) {
		int count = 0;
		for (int i = 0; i < data.size(); i++)
			if (data[i] >= 48 && data[i] <= 57) count++;
		if (!count) return false;
	}
	if (consider_special_signs) {
		int count = 0;
		for (int i = 0; i < data.size(); i++)
			if (data[i] == '_') ctr++;
		if (!count) return false;
	}

	return true;
}
