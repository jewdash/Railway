#include "accounts.h"
#include "checkings.h"
#include "console_settings.h"

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