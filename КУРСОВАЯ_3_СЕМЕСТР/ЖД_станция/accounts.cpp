#include "accounts.h"
#include "checkings.h"
#include "console_settings.h"

void Account::sign_in() {}

void Account::sign_up() {
	system("cls");
	SetConsoleTextAttribute(hStdOut, 15);
	cout << "\n РЕГИСТРАЦИЯ АККАУНТА\n\n";
	while (1) {
		SetConsoleTextAttribute(hStdOut, 7);
		cout << " Придумайте логин: ";
		SetConsoleTextAttribute(hStdOut, 14);
		ConsoleCursorVisible(true, 100);
		getline(cin, login);
		ConsoleCursorVisible(false, 100);
		if (!checkAuthorization(8, 64, login, false, false)) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl;
			cout << " НЕКОРРЕКТНО ВВЕДЁН ЛОГИН.\n";
			cout << " Размер логина должен составлять от 8 до 64 символов\n Логин должен состоять как минимум из одной буквы\n";
			SetConsoleTextAttribute(hStdOut, 4);
			cout << endl;
			Sleep(2000);
			cout << " Нажмите на любую клавишу если вам всё понятно и повторно введите логин . . .";
			if (_getch()) {}
			setCursorToXY(0, 3);
			for (int i = 0; i < 10; i++)
				cout << "                                                                                                                     \n";
			setCursorToXY(0, 3);
			continue;
		}
		else break;
	}

	while (1) {
		SetConsoleTextAttribute(hStdOut, 7);
		cout << "\n Придумайте пароль: ";
		SetConsoleTextAttribute(hStdOut, 14);
		ConsoleCursorVisible(true, 100);
		getline(cin, password);
		ConsoleCursorVisible(false, 100);
		if (!checkAuthorization(8, 20, password, true, true)) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl;
			cout << " НЕКОРРЕКТНО ВВЕДЁН ПАРОЛЬ.\n";
			cout << " Размер пароля должен составлять от 8 до 20 символов\n Пароль должен состоять как минимум из одной буквы, одной цифры и знака нижнего подчёркивания\n";
			SetConsoleTextAttribute(hStdOut, 4);
			cout << endl;
			Sleep(2000);
			cout << " Нажмите на любую клавишу если вам всё понятно и придумайте новый пароль . . .";
			if (_getch()) {}
			setCursorToXY(0, 4);
			for (int i = 0; i < 10; i++)
				cout << "                                                                                                                     \n";
			setCursorToXY(0, 4);
			continue;
		}
		else break;
	}
}
//bool Account::writeInfo() { return true; }
//bool Account::readInfo() { return true; }

void Account::display_tickets() {}
void Account::sort_tickets() {}
void Account::filter_tickets() {}
void Account::find_ticket() {}

//////////////////////////////////////

void UserAcc::display_tickets() {}
void UserAcc::sort_tickets() {}
void UserAcc::filter_tickets() {}
void UserAcc::find_ticket() {}

void UserAcc::sign_in() {
	Account::sign_in();
}

void UserAcc::sign_up() {
	Account::sign_up();
	balance = 0;
}

void UserAcc::fill_balance() {}
void UserAcc::see_balance() {}
void UserAcc::buy_ticket() {}
void UserAcc::check_history() {}

bool UserAcc::readInfo() { return true; }
bool UserAcc::writeInfo() {
	try {
		ofstream fout;
		fout.open("user.txt", ios::trunc & ios::app);
		if (!fout) throw "Ошибка открытия файла";

		fout << login << "\t" << password << "\t" << balance;
		fout.close();
		return true;
	}
	catch (const char* exc) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " Произошла ошибка: " << exc << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		cout << endl;
		Sleep(2000);
		cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
		if (_getch()) {}
		return false;
	}
}

ostream& operator<<(ostream& stream, UserAcc& user) {
	stream << user.login << "\t" << user.password << "\t" << user.balance << endl;
	return stream;
}

istream& operator>>(istream& stream, UserAcc& user) {
	stream >> user.login >> user.password >> user.balance;
	return stream;
}

UserAcc UserAcc::operator=(UserAcc user1) {
	login = user1.login;
	password = user1.password;
	balance = user1.balance;
	return *this;
}

//////////////////////////////////////

void AdminAcc::display_tickets() {}
void AdminAcc::sort_tickets() {}
void AdminAcc::filter_tickets() {}
void AdminAcc::find_ticket() {}

void AdminAcc::display_stations() {}
void AdminAcc::sort_stations() {}
void AdminAcc::filter_stations() {}
void AdminAcc::find_station() {}

void AdminAcc::sign_in() {
	Account::sign_in();
}
void AdminAcc::sign_up() { 
	Account::sign_up();
}

void AdminAcc::create_ticket() {}
void AdminAcc::delete_ticket() {}
void AdminAcc::edit_ticket() {}

void AdminAcc::add_station() {}
void AdminAcc::remove_station() {}
void AdminAcc::edit_station() {}

bool AdminAcc::readInfo() { return true; }
bool AdminAcc::writeInfo() {
	try {
		ofstream fout;
		fout.open("admin.txt", ios::trunc & ios::app);
		if (!fout) throw "Ошибка открытия файла";

		fout << login << "\t" << password;
		fout.close();
		return true;
	}
	catch (const char* exc) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " Произошла ошибка: " << exc << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		cout << endl;
		Sleep(2000);
		cout << " Нажмите на любую клавишу если вам всё понятно и попробуйте снова . . .";
		if (_getch()) {}
		return false;
	}
}

ostream& operator<<(ostream& stream, AdminAcc& user) {
	stream << user.login << "\t" << user.password << "\t" << endl;
	return stream;
}

istream& operator>>(istream& stream, AdminAcc& user) {
	stream >> user.login >> user.password;
	return stream;
}

AdminAcc AdminAcc::operator=(AdminAcc adm1) {
	login = adm1.login;
	password = adm1.password;
	return *this;
}