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
		cout << " ДАТА: " << endl;
		cout << " --- День: "; is >> dt.dd;
		cout << " --- Месяц: "; is >> dt.mm;
		cout << " --- Год: "; is >> dt.yyyy;
		cout << " ВРЕМЯ: " << endl;
		cout << " --- Часы: "; is >> dt.hh;
		cout << " --- Минуты: "; is >> dt.mt;

		if (!checkDateTime(dt)) {
			SetConsoleTextAttribute(hStdOut, 12);
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
	cout.fill('0');
	cout << setw(2) << dt.dd << "."
		<< setw(2) << dt.mm << "."
		<< setw(4) << dt.yyyy;
	cout.fill(' '); cout << "   ";
	cout.fill('0');
	cout << setw(2) << dt.hh << ":"
		<< setw(2) << dt.mt;
	return os;
}

ifstream& operator >> (ifstream& fis, DateTime& dt) {
	fis >> dt.dd >> dt.mm >> dt.yyyy >> dt.hh >> dt.mt;
	return fis;
}

ofstream& operator << (ofstream& fos, DateTime& dt) {
	fos << dt.dd << "\t" << dt.mm << "\t" << dt.yyyy << "\t" << dt.hh << "\t" << dt.mt;
	return fos;
}