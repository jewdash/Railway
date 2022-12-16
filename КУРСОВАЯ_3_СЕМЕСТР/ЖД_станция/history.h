#pragma once
#include "accounts.h"
#include "checkings.h"
#include "console_settings.h"
#include "SmartPtr.h"
#include "SmartPtr.cpp"
#include <memory>
#include <fstream>
#include <string>

using namespace std;
using namespace additional_funcs;

class History {
protected:
	DateTime buy_date;
	Ticket bought;
	int sold_num;
	int sum;
	static int history_size;
	static vector<SmartPointer<History>> hist;
	friend class UserAccount;
public:
	History() {
		buy_date = date_today();
		sold_num = 0;
		sum = 0;
	}

	History(DateTime buy_date, Ticket bought, int sold, int sum) {
		this->buy_date = buy_date;
		this->bought = bought;
		this->sold_num = sold;
		this->sum = sum;
	}

	~History() {}

	void set_history(History);
	SmartPointer<History> get_history();

	void set_buy_date(DateTime);
	DateTime get_buy_date();

	void set_bought(Ticket);
	Ticket get_bought();

	void set_sold(int);
	int get_sold();

	void set_sum(int);
	int get_sum();

	static vector<SmartPointer<History>> append_hist(History);
	void display_hist();
	static void read_hist();
	static void write_hist();
};
