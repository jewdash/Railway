#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

class Department {
protected:
	int code_department;
	string title;
	friend class UserAcc;
	friend class AdminAcc;
	friend class Station;
	friend class Ticket;
public:
	Department() : code_department(0), title("N/A") {}

	Department(int code, string title) {
		this->code_department = code;
		this->title = title;
	}

	int getCodeDep() { return code_department; }
	string getTitle() { return title; }
};

class Region {
protected:
	int code_region;
	string region;
	string district;
	friend class UserAcc;
	friend class AdminAcc;
	friend class Station; 
	friend class Ticket;
public:
	Region() : code_region(0), region("N/A"), district("N/A") {}

	Region(int code, string region, string district) {
		this->code_region = code;
		this->region = region;
		this->district = district;
	}

	//int getCodeReg() { return code_region; }
	//string getRegion() { return region; }
	//string getDistrict() { return district; }

	//void setCodeReg(int code_reg) { code_region = code_reg; }
	//void setRegion(string reg) { region = reg; }
	//void setDistrict(string dist) { district = dist; }
};

class Station {
protected:
	int id_station;
	string name_station;
	Department dep;
	Region region;
	friend class UserAcc;
	friend class AdminAcc;
	friend class Ticket;
public:
	Station() : id_station(0), name_station("N/A"), dep(0, "N/A"), region(0, "N/A", "N/A") {}
	Station(int id, Department dep, Region region, string name_station) {
		this->id_station = id;
		this->name_station = name_station;
		this->dep = dep;
		this->region = region;
	}

	
	bool writeStation();
	bool readStation();
};
