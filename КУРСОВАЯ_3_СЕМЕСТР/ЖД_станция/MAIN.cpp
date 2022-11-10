#include "accounts.h"
#include "State.h"
#include "SmartPtr.h"
#include "SmartPtr.cpp"
#include "console_settings.h"
#include "checkings.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <vector>

#define ENTER 13
#define BACKSPACE 8
#define ESC 27
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_RIGHT 77
#define ARROW_LEFT 75

using namespace std;

AdminAcc admin_account;
UserAcc user_account;
int state = State::logged_out;

void menu();
void admins_menu();
void users_menu();

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SetConsoleTitle(L"����������� �������� ������");
	ConsoleCursorVisible(false, 100);

	setCursorToXY(35, 13);
	cout << "��� ������������ ����������� �������� ������!!!";

	Sleep(3000);
	setCursorToXY(5, 25);
	SetConsoleTextAttribute(hStdOut, 8);
	ConsoleCursorVisible(false, 100);
	cout << "������� ����� �������, ����� ���������� . . .";
	if (_getch()) {}
	system("cls");

	while (1) {
		switch (state) {
		case State::logged_out: menu(); break;
		case State::admin: admins_menu(); break;
		case State::user: users_menu(); break;
		default: cout << "\n����������� ���������\n";
			exit(-1);
		}
	}
	return 0;
}

void menu() {
	system("cls");

	string actions[] = { "����������� (�����)", "���� (�����)", "����������� (������������)", "���� (������������)"};
	int activated = 0;
	ConsoleCursorVisible(false, 100);
	char ch;
	while (1) {
		/*system("cls");*/
		SetConsoleTextAttribute(hStdOut, 15);
		setCursorToXY(5, 1);
		cout << "��� ������ ����������������� ��� ������� � �������";
		setCursorToXY(5, 5);
		int y = 5;
		SetConsoleTextAttribute(hStdOut, 7);
		for (int i = 0; i < size(actions); i++) {
			if (i == activated) {
				SetConsoleTextAttribute(hStdOut, 11);
				cout << "> " << actions[i] << endl;
			}
			else {
				SetConsoleTextAttribute(hStdOut, 3);
				cout << actions[i] << "   " << endl;
			}
			setCursorToXY(5, y += 2);
		}
		SetConsoleTextAttribute(hStdOut, 8);
		cout << "Enter - ����������� �����, Esc - ����� �� ���������";
		ch = _getch();
		if (ch == -32) ch = _getch();
		
		switch (ch) {
		case ESC: 
			system("cls");
			SetConsoleTextAttribute(hStdOut, 7);
			setCursorToXY(35, 13);
			cout << "������� �� ����� ����������� �������� �����!";
			Sleep(3000);
			SetConsoleTextAttribute(hStdOut, 0); exit(0);
		case ARROW_UP:
			--activated;
			if (activated < 0)
				activated = size(actions) - 1;
			break;
		case ARROW_DOWN:
			++activated;
			if (activated == size(actions))
				activated = 0;
			break;
		case ENTER:
			switch (activated)
			{
			case 0: {
				admin_account.sign_up();
				string confirm;
				string admin_key;
				try {
					ifstream fin;
					fin.open("admin_key.txt", ios::in);
					if (!fin) throw "������ �������� �����";

					fin >> admin_key;
					fin.close();

					SetConsoleTextAttribute(hStdOut, 7);
					cout << "\n ������� ���� ��������������: ";
					SetConsoleTextAttribute(hStdOut, 14);
					ConsoleCursorVisible(true, 100);
					getline(cin, confirm);
					ConsoleCursorVisible(false, 100);

					if (confirm != admin_key) throw "�������� ���� ��������������";

					if (admin_account.writeInfo()) {
						SetConsoleTextAttribute(hStdOut, 10);
						cout << endl << endl;
						cout << " �� ������� ������������������.\n";
						cout << " ������ � ����� �������� ������ �������� � �����\n ��� ��������� ����������� ������ ����� ������� � �� �� ����� ����� �������� �����\n";
						SetConsoleTextAttribute(hStdOut, 2);
						cout << endl;
						Sleep(2000);
						cout << " ������� �� ����� ������� ���� ��� �� ������� � ������� ���������� . . .";
						if (_getch()) {}
						state = State::admin;
					}
					else state = State::logged_out;
				}
				catch (const char* exc) {
					SetConsoleTextAttribute(hStdOut, 12);
					cout << endl << endl << " ��������� ������: " << exc << endl;
					SetConsoleTextAttribute(hStdOut, 4);
					cout << endl;
					Sleep(2000);
					cout << " ������� �� ����� ������� ���� ��� �� ������� � ���������� ����� . . .";
					if (_getch()) {}
				}
				break; //reg as admin
			}
			case 1: {
				string confirm;
				string admin_key;
				try {
					AdminAcc acc;
					if (!admin_account.readInfo()) throw "������ ���������� �� �����";
					acc.sign_in();

					ifstream fin;
					fin.open("admin_key.txt", ios::in);
					if (!fin) throw "������ �������� �����";

					fin >> admin_key;
					fin.close();

					SetConsoleTextAttribute(hStdOut, 7);
					cout << "\n ������� ���� ��������������: ";
					SetConsoleTextAttribute(hStdOut, 14);
					ConsoleCursorVisible(true, 100);
					getline(cin, confirm);
					ConsoleCursorVisible(false, 100);

					if (confirm != admin_key) throw "�������� ���� ��������������";

					if (!admin_account.loginCorrect(acc)) throw "�������� ����� ��� ������";

					SetConsoleTextAttribute(hStdOut, 10);
					cout << endl << endl;
					cout << " �� ������� ����� � �������.\n";
					cout << " ��� ������ �� �������� ������� Backspace\n ��� ����� ������ �������� ��������������� �����. ��� ���� ������ ������ ����� �������\n";
					SetConsoleTextAttribute(hStdOut, 2);
					cout << endl;
					Sleep(2000);
					cout << " ������� �� ����� ������� ���� ��� �� ������� � ������� ���������� . . .";
					if (_getch()) {}
					state = State::admin;
				}
				catch (const char* exc) {
					SetConsoleTextAttribute(hStdOut, 12);
					cout << endl << endl << " ��������� ������: " << exc << endl;
					SetConsoleTextAttribute(hStdOut, 4);
					cout << endl;
					Sleep(2000);
					cout << " ������� �� ����� ������� ���� ��� �� ������� � ���������� ����� . . .";
					if (_getch()) {}
				}
				break; //enter as admin
			}
			case 2: {
				user_account.sign_up();
				if (user_account.writeInfo()) {
					SetConsoleTextAttribute(hStdOut, 10);
					cout << endl << endl;
					cout << " �� ������� ������������������.\n";
					cout << " ������ � ����� �������� ������ �������� � �����\n ��� ��������� ����������� ������ ����� ������� � �� �� ����� ����� �������� �����\n";
					SetConsoleTextAttribute(hStdOut, 2);
					cout << endl;
					Sleep(2000);
					cout << " ������� �� ����� ������� ���� ��� �� ������� � ������� ���������� . . .";
					if (_getch()) {}
					state = State::user;
				}
				else state = State::logged_out;
				break; //reg as user
			}
			case 3: {
				try {
					UserAcc acc;
					if (!user_account.readInfo()) throw "������ ���������� �� �����";
					acc.sign_in();

					if (!user_account.loginCorrect(acc)) throw "�������� ����� ��� ������";

					SetConsoleTextAttribute(hStdOut, 10);
					cout << endl << endl;
					cout << " �� ������� ����� � �������.\n";
					cout << " ��� ������ �� �������� ������� Backspace\n ��� ����� ������ �������� ��������������� �����. ��� ���� ������ ������ ����� �������\n";
					SetConsoleTextAttribute(hStdOut, 2);
					cout << endl;
					Sleep(2000);
					cout << " ������� �� ����� ������� ���� ��� �� ������� � ������� ���������� . . .";
					if (_getch()) {}
					state = State::user;
				}
				catch (const char* exc) {
					SetConsoleTextAttribute(hStdOut, 12);
					cout << endl << endl << " ��������� ������: " << exc << endl;
					SetConsoleTextAttribute(hStdOut, 4);
					cout << endl;
					Sleep(2000);
					cout << " ������� �� ����� ������� ���� ��� �� ������� � ���������� ����� . . .";
					if (_getch()) {}
				}
				break; //enter as user
			}
			}
			return;
		default: continue;
		}
	}
}

void admins_menu() {
	system("cls");

	string actions[] = { "�������� �����",
		"������� �����",
		"����������� ������",
		"������������� �����",
		"����� ������",
		"���������� �������",
		"���������� �������",
	//////////////////////////////////
		"�������� �������",
		"������� �������",
		"����������� �������",
		"������������� �������",
		"����� �������",
		"���������� �������",
		"���������� �������"
	};

	int activated = 0;
	ConsoleCursorVisible(false, 100);
	char ch;
	while (1) {
		/*system("cls");*/
		SetConsoleTextAttribute(hStdOut, 15);
		setCursorToXY(5, 1);
		cout << "������ ��������������. �������� ��������";
		setCursorToXY(5, 5);
		int y = 5;
		SetConsoleTextAttribute(hStdOut, 7);
		for (int i = 0; i < size(actions) / 2; i++) {
			if (i == activated) {
				SetConsoleTextAttribute(hStdOut, 11);
				cout << "> " << actions[i] << endl;
			}
			else {
				SetConsoleTextAttribute(hStdOut, 3);
				cout << actions[i] << "     " << endl;
			}
			setCursorToXY(5, y += 2);
		}

		y = 5;
		setCursorToXY(40, y);
		SetConsoleTextAttribute(hStdOut, 7);
		for (int i = size(actions) / 2; i < size(actions); i++) {
			if (i == activated) {
				SetConsoleTextAttribute(hStdOut, 11);
				cout << "> " << actions[i] << endl;
			}
			else {
				SetConsoleTextAttribute(hStdOut, 3);
				cout << actions[i] << "    " << endl;
			}
			setCursorToXY(40, y += 2);
		}
		SetConsoleTextAttribute(hStdOut, 8);
		setCursorToXY(5, y + 1);
		cout << "Enter - ����������� �����, Esc - ����� �� ���������, Backspace - ����� �� ��������";
		ch = _getch();
		if (ch == -32) ch = _getch();

		switch (ch) {
		case BACKSPACE:
			system("cls");
			SetConsoleTextAttribute(hStdOut, 7);
			setCursorToXY(35, 13);
			cout << "�� ����� �� ��������! ������� �� ������!";
			Sleep(3000);
			setCursorToXY(5, 25);
			SetConsoleTextAttribute(hStdOut, 8);
			ConsoleCursorVisible(false, 100);
			cout << "������� ����� �������, ����� ���������� . . .";
			if (_getch()) {}
			state = State::logged_out;
			system("cls");
			return;
		case ESC:
			system("cls");
			SetConsoleTextAttribute(hStdOut, 7);
			setCursorToXY(35, 13);
			cout << "������� �� ����� ����������� �������� �����!";
			Sleep(3000);
			SetConsoleTextAttribute(hStdOut, 0); exit(0);
		case ARROW_UP:
			--activated;
			if (activated < 0)
				activated = size(actions) - 1;
			break;
		case ARROW_DOWN:
			++activated;
			if (activated == size(actions))
				activated = 0;
			break;
		case ARROW_LEFT:
			if (activated >= (size(actions) / 2) && activated < size(actions))
				activated -= (size(actions) / 2);
			else activated += (size(actions) / 2);
			break;
		case ARROW_RIGHT:
			if (activated >= 0 && activated < (size(actions) / 2))
				activated += (size(actions) / 2);
			else activated -= (size(actions) / 2);
			break;
		case ENTER:
			switch (activated)
			{
			case 0: break; 
			case 1: break; 
			case 2: break; 
			case 3: break;
			case 4: break;
			case 5: break;
			case 6: break;

			case 7: break;
			case 8: break;
			case 9: break;
			case 10: break;
			case 11: break;
			case 12: break;
			case 13: break;
			}
			break;
		default: continue;
		}
	}
}

void users_menu() {
	system("cls");

	string actions[] = {
		"����������� ������",
		"����� ������",
		"���������� �������",
		"���������� �������",
		//////////////////////////////////
		"��������� ������",
		"����������� ������",
		"������ �����",
		"������� �������"
	};

	int activated = 0;
	ConsoleCursorVisible(false, 100);
	char ch;
	while (1) {
		/*system("cls");*/
		SetConsoleTextAttribute(hStdOut, 15);
		setCursorToXY(5, 1);
		cout << "������ ������������. �������� ��������";
		setCursorToXY(5, 5);
		int y = 5;
		SetConsoleTextAttribute(hStdOut, 7);
		for (int i = 0; i < size(actions) / 2; i++) {
			if (i == activated) {
				SetConsoleTextAttribute(hStdOut, 11);
				cout << "> " << actions[i] << endl;
			}
			else {
				SetConsoleTextAttribute(hStdOut, 3);
				cout << actions[i] << "    " << endl;
			}
			setCursorToXY(5, y += 2);
		}

		y = 5;
		setCursorToXY(40, y);
		SetConsoleTextAttribute(hStdOut, 7);
		for (int i = size(actions) / 2; i < size(actions); i++) {
			if (i == activated) {
				SetConsoleTextAttribute(hStdOut, 11);
				cout << "> " << actions[i] << endl;
			}
			else {
				SetConsoleTextAttribute(hStdOut, 3);
				cout << actions[i] << "    " << endl;
			}
			setCursorToXY(40, y += 2);
		}
		SetConsoleTextAttribute(hStdOut, 8);
		setCursorToXY(5, y + 1);
		cout << "Enter - ����������� �����, Esc - ����� �� ���������, Backspace - ����� �� ��������";
		ch = _getch();
		if (ch == -32) ch = _getch();

		switch (ch) {
		case BACKSPACE:
			system("cls");
			SetConsoleTextAttribute(hStdOut, 7);
			setCursorToXY(35, 13);
			cout << "�� ����� �� ��������! ������� �� ������!";
			Sleep(3000);
			setCursorToXY(5, 25);
			SetConsoleTextAttribute(hStdOut, 8);
			ConsoleCursorVisible(false, 100);
			cout << "������� ����� �������, ����� ���������� . . .";
			if (_getch()) {}
			state = State::logged_out;
			system("cls");
			return;
		case ESC:
			system("cls");
			SetConsoleTextAttribute(hStdOut, 7);
			setCursorToXY(35, 13);
			cout << "������� �� ����� ����������� �������� �����!";
			Sleep(3000);
			SetConsoleTextAttribute(hStdOut, 0); exit(0);
		case ARROW_UP:
			--activated;
			if (activated < 0)
				activated = size(actions) - 1;
			break;
		case ARROW_DOWN:
			++activated;
			if (activated == size(actions))
				activated = 0;
			break;
		case ARROW_LEFT:
			if (activated >= (size(actions) / 2) && activated < size(actions))
				activated -= (size(actions) / 2);
			else activated += (size(actions) / 2);
			break;
		case ARROW_RIGHT:
			if (activated >= 0 && activated < (size(actions) / 2))
				activated += (size(actions) / 2);
			else activated -= (size(actions) / 2);
			break;
		case ENTER:
			switch (activated)
			{
			case 0: break;
			case 1: break;
			case 2: break;
			case 3: break;

			case 4: break;
			case 5: break;
			case 6: break;
			case 7: break;
			}
			break;
		default: continue;
		}
	}
}