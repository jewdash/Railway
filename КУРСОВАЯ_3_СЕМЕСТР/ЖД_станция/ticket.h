#pragma once

#include "station.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <queue>

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
	DateTime getDepDate();
	DateTime getArrDate();
};

class CompareDate {
public:
	bool operator()(Ticket& td1, Ticket& td2);
};