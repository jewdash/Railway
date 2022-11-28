#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <vector>
#include "console_settings.h"
#include "checkings.h"

using namespace std;

class Account {
protected:
	string login;
	string password;
public:
	Account() :
		login("jewdash003"),
		password("oral_cumshot")
	{}

	Account(string login, string password) {
		this->login = login;
		this->password = password;
	}

	Account(const Account& obj) {
		this->login = obj.login;
		this->password = obj.password;
	}

	virtual void sign_in();
	virtual void sign_up();

	//virtual bool writeInfo();
	//virtual bool readInfo();

	virtual void display_tickets();
	virtual void sort_tickets();
	virtual void filter_tickets();
	virtual void find_ticket();

	virtual bool loginCorrect() { return true; }
};

class UserAcc : public Account {
protected:
	int balance;
public:
	UserAcc() :
		balance(0)
	{}

	UserAcc(int balance) {
		this->balance = balance;
	}

	//UserAcc(const UserAcc& obj) {
	//	this->balance = obj.balance;
	//}

	void display_tickets();
	void sort_tickets();
	void filter_tickets();
	void find_ticket();

	void sign_in();
	void sign_up();

	void fill_balance();
	void see_balance();
	void buy_ticket();
	void check_history();

	bool readInfo();
	bool writeInfo();

	friend ostream& operator<<(ostream&, UserAcc&);
	friend istream& operator>>(istream&, UserAcc&);
	friend istream& operator>>(istream&, string&);
	UserAcc operator=(UserAcc);
	bool loginCorrect(UserAcc user) {
		if (!Account::loginCorrect()) return false;
		if (login == user.login && password == user.password) return true;
		else return false;
	}
};

class AdminAcc : public Account {
public:

	AdminAcc() {}

	void display_tickets();
	void sort_tickets();
	void filter_tickets();
	void find_ticket();

	void display_stations();
	void sort_stations();
	void filter_stations();
	void find_station();

	void sign_in();
	void sign_up();

	void create_ticket();
	void delete_ticket();
	void edit_ticket();

	void add_station();
	void remove_station();
	void edit_station();

	bool readInfo();
	bool writeInfo();

	friend ostream& operator<<(ostream&, AdminAcc&);
	friend istream& operator>>(istream&, AdminAcc&);
	AdminAcc operator=(AdminAcc);
	bool loginCorrect(AdminAcc adm) {
		if (!Account::loginCorrect()) return false;
		if (login == adm.login && password == adm.password) return true;
		else return false;
	}
};
