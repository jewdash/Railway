#include "accounts.h"
#include "checkings.h"
#include "console_settings.h"
#include "ticket.h"
#include <iomanip>

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

ostream& operator<<(ostream& stream, AdminAcc& adm) {
	stream << adm.login << "\t" << adm.password << "\t" << endl;
	return stream;
}

istream& operator>>(istream& stream, AdminAcc& adm) {
	stream >> adm.login >> adm.password;
	return stream;
}

AdminAcc AdminAcc::operator=(AdminAcc adm1) {
	login = adm1.login;
	password = adm1.password;
	return *this;
}

////////////////////////////////////////////////////////////

bool operator == (DateTime dt_1, DateTime dt_2) {
	if (dt_1.yyyy != dt_2.yyyy) return false;
	else {
		if (dt_1.mm != dt_2.mm) return false;
		else {
			if (dt_1.dd != dt_2.dd) return false;
			else {
				if (dt_1.hh != dt_2.hh) return false;
				else {
					if (dt_1.mt != dt_2.mt) return false;
					else return true;
				}
			}
		}
	}
}

bool operator < (DateTime dt_1, DateTime dt_2) {
	if (dt_1.yyyy < dt_2.yyyy) return true;
	if (dt_1.yyyy > dt_2.yyyy) return false;
	else {
		if ((dt_1.yyyy == dt_2.yyyy) && (dt_1.mm < dt_2.mm)) return true;
		if ((dt_1.yyyy == dt_2.yyyy) && (dt_1.mm > dt_2.mm)) return false;
		else {
			if ((dt_1.mm == dt_2.mm) && (dt_1.dd < dt_2.dd)) return true;
			if ((dt_1.mm == dt_2.mm) && (dt_1.dd > dt_2.dd)) return false;
			else {
				if ((dt_1.dd == dt_2.dd) && (dt_1.hh < dt_2.hh)) return true;
				if ((dt_1.dd == dt_2.dd) && (dt_1.hh > dt_2.hh)) return false;
				else {
					if ((dt_1.hh == dt_2.hh) && (dt_1.mt < dt_2.mt)) return true;
					if ((dt_1.hh == dt_2.hh) && (dt_1.mt > dt_2.mt)) return false;
					else {
						if (dt_1.mt == dt_2.mt) return false;
					}
				}
			}
		}
	}
}

bool operator > (DateTime dt_1, DateTime dt_2) {
	if (dt_1.yyyy > dt_2.yyyy) return true;
	if (dt_1.yyyy < dt_2.yyyy) return false;
	else {
		if ((dt_1.yyyy == dt_2.yyyy) && (dt_1.mm > dt_2.mm)) return true;
		if ((dt_1.yyyy == dt_2.yyyy) && (dt_1.mm < dt_2.mm)) return false;
		else {
			if ((dt_1.mm == dt_2.mm) && (dt_1.dd > dt_2.dd)) return true;
			if ((dt_1.mm == dt_2.mm) && (dt_1.dd < dt_2.dd)) return false;
			else {
				if ((dt_1.dd == dt_2.dd) && (dt_1.hh > dt_2.hh)) return true;
				if ((dt_1.dd == dt_2.dd) && (dt_1.hh < dt_2.hh)) return false;
				else {
					if ((dt_1.hh == dt_2.hh) && (dt_1.mt > dt_2.mt)) return true;
					if ((dt_1.hh == dt_2.hh) && (dt_1.mt < dt_2.mt)) return false;
					else {
						if (dt_1.mt == dt_2.mt) return false;
					}
				}
			}
		}
	}
}

istream& operator >> (istream& is, DateTime& dt) {
	while (1) {
		cout << endl << endl;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << " ДАТА: " << endl;
		cout << "  --- День: "; 
		SetConsoleTextAttribute(hStdOut, 14); ConsoleCursorVisible(true, 100); is >> dt.dd;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << "  --- Месяц: "; 
		SetConsoleTextAttribute(hStdOut, 14); ConsoleCursorVisible(true, 100); is >> dt.mm;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << "  --- Год: "; 
		SetConsoleTextAttribute(hStdOut, 14); ConsoleCursorVisible(true, 100); is >> dt.yyyy;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << " ВРЕМЯ: " << endl;
		cout << "  --- Часы: "; 
		SetConsoleTextAttribute(hStdOut, 14); ConsoleCursorVisible(true, 100); is >> dt.hh;
		SetConsoleTextAttribute(hStdOut, 15);
		cout << "  --- Минуты: "; 
		SetConsoleTextAttribute(hStdOut, 14); ConsoleCursorVisible(true, 100); is >> dt.mt;
		SetConsoleTextAttribute(hStdOut, 15);

		if (!checkDateTime(dt)) {
			SetConsoleTextAttribute(hStdOut, 12);
			ConsoleCursorVisible(false, 100);
			cout << endl << endl << " Ошибка ввода даты! " << endl;
			SetConsoleTextAttribute(hStdOut, 4);
			cout << endl;
			Sleep(2000);
			cout << " Нажмите на любую клавишу и попробуйте снова . . .";
			if (_getch()) {}
			continue;
		}
		else break;
	}
	return is;
}

ostream& operator << (ostream& os, DateTime& dt) {
	os.fill('0');
	os << setw(2) << dt.dd << "."
		<< setw(2) << dt.mm << "."
		<< setw(4) << dt.yyyy;
	os.fill(' '); cout << "   ";
	os.fill('0');
	os << setw(2) << dt.hh << ":"
		<< setw(2) << dt.mt;

	cout.fill(' ');
	return os;
}