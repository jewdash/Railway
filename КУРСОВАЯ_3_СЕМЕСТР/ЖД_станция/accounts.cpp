#include "accounts.h"
#include "checkings.h"
#include "console_settings.h"

bool Account::sign_in() { return true; }

bool Account::sign_up() {
	system("cls");
	SetConsoleTextAttribute(hStdOut, 15);
	cout << "\n РЕГИСТРАЦИЯ АККАУНТА\n\n";
	while (1) {
		SetConsoleTextAttribute(hStdOut, 7);
		cout << " Придумайте логин: ";
		SetConsoleTextAttribute(hStdOut, 14);
		getchar();
		getline(cin, login);
		if (checkAuthorization(8, 64, login, false, false)) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl;
			cout << " НЕКОРРЕКТНО ВВЕДЁН ЛОГИН.\n ";
			cout << " Размер логина должен составлять от 8 до 64 символов\n Логин должен состоять как минимум из одной буквы\n ";
			cout << " Нажмите на любую клавишу если вам всё понятно и повторно введите логин . . .";
			SetConsoleTextAttribute(hStdOut, 4);
			if (_getch()) {}
			setCursorToXY(4, 1);
			cout << string(10, '\n');
			setCursorToXY(4, 1);
			continue;
		}
	}
	return true;
}
void Account::writeInfo() {}
void Account::readInfo() {}

void Account::display_tickets() {}
void Account::sort_tickets() {}
void Account::filter_tickets() {}
void Account::find_ticket() {}

//////////////////////////////////////

void UserAcc::display_tickets() {}
void UserAcc::sort_tickets() {}
void UserAcc::filter_tickets() {}
void UserAcc::find_ticket() {}

bool UserAcc::sign_in() { return true; }
bool UserAcc::sign_up() { return true; }

void UserAcc::fill_balance() {}
void UserAcc::see_balance() {}
void UserAcc::buy_ticket() {}
void UserAcc::check_history() {}

void UserAcc::readInfo() {}
void UserAcc::writeInfo() {}

//////////////////////////////////////

void AdminAcc::display_tickets() {}
void AdminAcc::sort_tickets() {}
void AdminAcc::filter_tickets() {}
void AdminAcc::find_ticket() {}

void AdminAcc::display_stations() {}
void AdminAcc::sort_stations() {}
void AdminAcc::filter_stations() {}
void AdminAcc::find_station() {}

bool AdminAcc::sign_in() { return true; }
bool AdminAcc::sign_up() { return true; }

void AdminAcc::create_ticket() {}
void AdminAcc::delete_ticket() {}
void AdminAcc::edit_ticket() {}

void AdminAcc::add_station() {}
void AdminAcc::remove_station() {}
void AdminAcc::edit_station() {}

void AdminAcc::readInfo() {}
void AdminAcc::writeInfo() {}