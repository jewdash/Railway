#pragma once
#pragma warning(disable: 4996)

#include "station.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <queue>
#include <ctime>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class Date {
protected:
	int dd;
	int mm;
	int yyyy;
public:
	Date() : dd(1), mm(1), yyyy(1970) {}
};

class Time {
protected:
	int hh;
	int mt;
public:
	Time() : hh(0), mt(0) {}
};

class DateTime : public Date, public Time {
protected:
	friend class Ticket;
	friend class UserAcc;
	friend class AdminAcc;
	friend inline DateTime date_today();
public:
	DateTime() {}
	DateTime(int dd, int mm, int yyyy, int hh, int mt) {
		this->dd = dd;
		this->mm = mm;
		this->yyyy = yyyy;
		this->hh = hh;
		this->mt = mt;
	}

	friend bool operator == (DateTime dt_1, DateTime dt_2);
	friend bool operator < (DateTime dt_1, DateTime dt_2);
	friend bool operator > (DateTime dt_1, DateTime dt_2);
	friend istream& operator >> (istream& is, DateTime& dt);
	friend ostream& operator << (ostream& os, DateTime& dt);
	friend ifstream& operator >> (ifstream& fis, DateTime& dt);
	friend ofstream& operator << (ofstream& fos, DateTime& dt);

	int getY() { return yyyy; }
	int getMth() { return mm; }
	int getD() { return dd; }
	int getH() { return hh; }
	int getMts() { return mt; }
};

class Ticket {
protected:
	int id_ticket;
	DateTime dep_dt;
	Station dep_station;
	DateTime arr_dt;
	Station arr_station;
	int amount;
	int price;
	friend class UserAcc;
	friend class AdminAcc;
	friend class History;
public:
	Ticket() :
		id_ticket(0),
		dep_dt(DateTime()),
		dep_station(Station()),
		arr_dt(DateTime()),
		arr_station(Station()),
		amount(0),
		price(0) {}

	Ticket(
		int id,
		DateTime dep_dt,
		Station dep_station,
		DateTime arr_dt,
		Station arr_station,
		int amount,
		int price
	) {
		this->id_ticket = id;
		this->dep_dt = dep_dt;
		this->dep_station = dep_station;
		this->arr_dt = arr_dt;
		this->arr_station = arr_station;
		this->amount = amount;
		this->price = price;
	}

	bool writeTicket();
	bool readTicket(vector<Ticket>& tkv);
	int getID();
	DateTime getDepDate();
	DateTime getArrDate();
	string getDepStation();
	string getArrStation();
};

class CompareDate {
public:
	bool operator()(Ticket& td1, Ticket& td2);
};

DateTime date_today() {
	DateTime dt;
	time_t current = time(NULL);
	struct tm tm = *localtime(&current);

	dt.dd = tm.tm_mday;
	dt.mm = tm.tm_mon + 1;
	dt.yyyy = tm.tm_year + 1900;
	dt.hh = tm.tm_hour;
	dt.mt = tm.tm_min;

	return dt;
}