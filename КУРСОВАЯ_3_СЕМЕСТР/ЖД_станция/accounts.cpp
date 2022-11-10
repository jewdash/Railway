#include "accounts.h"
#include "checkings.h"
#include "console_settings.h"

void Account::sign_in() {
	system("cls");
	SetConsoleTextAttribute(hStdOut, 15);
	cout << "\n ���� � �������\n\n";
	while (1) {
		SetConsoleTextAttribute(hStdOut, 7);
		cout << " ������� �����: ";
		SetConsoleTextAttribute(hStdOut, 14);
		ConsoleCursorVisible(true, 100);
		getline(cin, login);
		ConsoleCursorVisible(false, 100);
		if (!checkAuthorization(8, 64, login, false, false)) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl;
			cout << " ����������� ���Ĩ� �����.\n";
			cout << " ������ ������ ������ ���������� �� 8 �� 64 ��������\n ����� ������ �������� ��� ������� �� ����� �����\n";
			SetConsoleTextAttribute(hStdOut, 4);
			cout << endl;
			Sleep(2000);
			cout << " ������� �� ����� ������� ���� ��� �� ������� � �������� ������� ����� . . .";
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
		cout << "\n ������� ������: ";
		SetConsoleTextAttribute(hStdOut, 14);
		ConsoleCursorVisible(true, 100);
		getline(cin, password);
		ConsoleCursorVisible(false, 100);
		if (!checkAuthorization(8, 20, password, true, true)) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl;
			cout << " ����������� ���Ĩ� ������.\n";
			cout << " ������ ������ ������ ���������� �� 8 �� 20 ��������\n ������ ������ �������� ��� ������� �� ����� �����, ����� ����� � ����� ������� �������������\n";
			SetConsoleTextAttribute(hStdOut, 4);
			cout << endl;
			Sleep(2000);
			cout << " ������� �� ����� ������� ���� ��� �� ������� � ���������� ����� ������ . . .";
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

void Account::sign_up() {
	system("cls");
	SetConsoleTextAttribute(hStdOut, 15);
	cout << "\n ����������� ��������\n\n";
	while (1) {
		SetConsoleTextAttribute(hStdOut, 7);
		cout << " ���������� �����: ";
		SetConsoleTextAttribute(hStdOut, 14);
		ConsoleCursorVisible(true, 100);
		getline(cin, login);
		ConsoleCursorVisible(false, 100);
		if (!checkAuthorization(8, 64, login, false, false)) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl;
			cout << " ����������� ���Ĩ� �����.\n";
			cout << " ������ ������ ������ ���������� �� 8 �� 64 ��������\n ����� ������ �������� ��� ������� �� ����� �����\n";
			SetConsoleTextAttribute(hStdOut, 4);
			cout << endl;
			Sleep(2000);
			cout << " ������� �� ����� ������� ���� ��� �� ������� � �������� ������� ����� . . .";
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
		cout << "\n ���������� ������: ";
		SetConsoleTextAttribute(hStdOut, 14);
		ConsoleCursorVisible(true, 100);
		getline(cin, password);
		ConsoleCursorVisible(false, 100);
		if (!checkAuthorization(8, 20, password, true, true)) {
			SetConsoleTextAttribute(hStdOut, 12);
			cout << endl << endl;
			cout << " ����������� ���Ĩ� ������.\n";
			cout << " ������ ������ ������ ���������� �� 8 �� 20 ��������\n ������ ������ �������� ��� ������� �� ����� �����, ����� ����� � ����� ������� �������������\n";
			SetConsoleTextAttribute(hStdOut, 4);
			cout << endl;
			Sleep(2000);
			cout << " ������� �� ����� ������� ���� ��� �� ������� � ���������� ����� ������ . . .";
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
//////////////////////////////////////
void UserAcc::sign_in() {
	Account::sign_in();
}

void UserAcc::sign_up() {
	Account::sign_up();
	balance = 0;
}

bool UserAcc::readInfo() {
	try {
		ifstream fin;
		fin.open("user.txt", ios::in);
		if (!fin) throw "������ �������� �����";

		fin >> *this;
		fin.close();
		return true;
	}
	catch (const char* exc) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " ��������� ������: " << exc << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		cout << endl;
		Sleep(2000);
		cout << " ������� �� ����� ������� ���� ��� �� ������� � ���������� ����� . . .";
		if (_getch()) {}
		return false;
	}
}
bool UserAcc::writeInfo() {
	try {
		ofstream fout;
		fout.open("user.txt", ios::trunc & ios::app);
		if (!fout) throw "������ �������� �����";

		fout << *this;
		fout.close();
		return true;
	}
	catch (const char* exc) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " ��������� ������: " << exc << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		cout << endl;
		Sleep(2000);
		cout << " ������� �� ����� ������� ���� ��� �� ������� � ���������� ����� . . .";
		if (_getch()) {}
		return false;
	}
}

void AdminAcc::sign_in() {
	Account::sign_in();
}

void AdminAcc::sign_up() { 
	Account::sign_up();
}

bool AdminAcc::readInfo() {
	try {
		ifstream fin;
		fin.open("admin.txt", ios::in);
		if (!fin) throw "������ �������� �����";

		fin >> *this;
		fin.close();
		return true;
	}
	catch (const char* exc) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " ��������� ������: " << exc << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		cout << endl;
		Sleep(2000);
		cout << " ������� �� ����� ������� ���� ��� �� ������� � ���������� ����� . . .";
		if (_getch()) {}
		return false;
	}
	return true;
}
bool AdminAcc::writeInfo() {
	try {
		ofstream fout;
		fout.open("admin.txt", ios::trunc & ios::app);
		if (!fout) throw "������ �������� �����";

		fout << *this;
		fout.close();
		return true;
	}
	catch (const char* exc) {
		SetConsoleTextAttribute(hStdOut, 12);
		cout << endl << endl << " ��������� ������: " << exc << endl;
		SetConsoleTextAttribute(hStdOut, 4);
		cout << endl;
		Sleep(2000);
		cout << " ������� �� ����� ������� ���� ��� �� ������� � ���������� ����� . . .";
		if (_getch()) {}
		return false;
	}
}
