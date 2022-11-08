#pragma once
#include <string>

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

	virtual bool sign_in() { return true; }
	virtual bool sign_up() { return true; }

	virtual void writeInfo() {}
	virtual void readInfo() {}

	virtual void display_tickets() {}
	virtual void sort_tickets() {}
	virtual void filter_tickets() {}
	virtual void find_ticket() {}
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

	UserAcc(const UserAcc& obj) {
		this->balance = obj.balance;
	}

	void display_tickets();
	void sort_tickets();
	void filter_tickets();
	void find_ticket();

	bool sign_in();
	bool sign_up();

	void fill_balance();
	void see_balance();
	void buy_ticket();
	void check_history();

	void readInfo();
	void writeInfo();
};

class AdminAcc : public Account {
protected:
	string confirm;
public:
	AdminAcc() : Account(),
		confirm("") {}

	AdminAcc(string confirm) {
		this->confirm = confirm;
	}

	AdminAcc(const AdminAcc& obj) {
		this->confirm = obj.confirm;
	}

	~AdminAcc() {}

	void display_tickets();
	void sort_tickets();
	void filter_tickets();
	void find_ticket();

	void display_stations();
	void sort_stations();
	void filter_stations();
	void find_station();

	bool sign_in();
	bool sign_up();

	void create_ticket();
	void delete_ticket();
	void edit_ticket();

	void add_station();
	void remove_station();
	void edit_station();

	void readInfo();
	void writeInfo();
};
